#include <stdio.h>
#include <pthread.h>

template <class V>
class SecureStack
{
    private:
    int size;
    int index = 0;
    V* array;
    pthread_mutex_t lock;
    pthread_cond_t emptyCondition;
    pthread_cond_t fullCondition;
    public:
    SecureStack(int _size):size(_size){
        pthread_mutex_init(&lock,NULL);
        pthread_cond_init(&emptyCondition,NULL);
        pthread_cond_init(&fullCondition,NULL);
        array = new V[_size];
    }
    ~SecureStack() { 
        delete [] array;
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&emptyCondition);
        pthread_cond_destroy(&fullCondition);
    }

    void add(V element)
    {
        pthread_mutex_lock(&lock);

        while(index >= size)
            pthread_cond_wait(&fullCondition,&lock);
        
        array[index] = element;
        index += 1;

        pthread_cond_signal(&emptyCondition);
        pthread_mutex_unlock(&lock);
    }

    V remove()
    {
        V value;
        pthread_mutex_lock(&lock);
        while(index == 0)
            pthread_cond_wait(&emptyCondition,&lock);

        value = array[index];
        index -= 1;
        
        pthread_cond_signal(&fullCondition);
        pthread_mutex_unlock(&lock);
        return value;

    }

    V read()
    {
        V value = 5;
        pthread_mutex_lock(&lock);
        value = array[index];
        pthread_mutex_unlock(&lock);
        return value;
    }
};


SecureStack<int> stack(10);

void* run(void* args)
{
    int* id = (int*) args;
    printf("ID: %d\n",*id);
    for(int i = 0;i < 100;i++)
    {
        printf("TRY\n");
        if(*id % 2 == 1)
            stack.add(i);
        else
            stack.remove();
    }

    delete id;
    return NULL;
}

int main()
{


    stack.add(1);

    pthread_t threads[3];
    for(int i = 0;i < 3;i++)
    {
        pthread_create(&threads[i],NULL,&run,new int(i));
    }
    for(int i = 0;i < 3;i++)
        pthread_join(threads[i],NULL);

    
    

    return 0;

}