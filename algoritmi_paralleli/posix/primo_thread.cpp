#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


//nella fase di linking è necessario specificare la libraria del pthread
//comando con gcc : g++ <nome file> -pthread -o <nome file output)

void* firstHello(void* arg)
{                                                               
    printf("Hello world\n");
    return NULL;
}

void* hello(void* arg)
{  
    printf("Stampo il numero: %d \n", *(int*)arg);

    //cancelliamo la int allocata
    delete (int*)arg;
    return NULL;
}


int main()
{

    //puntatore dell' ID del thread
    pthread_t pid;
    pthread_create(&pid,NULL,&firstHello,NULL);




    pthread_t threads[10];

    for(int i = 0;i < 10;i++)
    {
        //abbiamo creato una copia perchè altrimenti i thread arrivano dopo e trovano la unica i a 10
        //quindi è necessario passare ad ogni thread un nuovo int allocato, che poi verrà fatto delete per deallocare
        int* copy = new int(i);
        pthread_create(&threads[i],NULL,&hello,copy);
        //non è buono perche ogni thread aspetto quello antecedente
        //pthread_join(threads[i],NULL);
    }




    //solo ora viene fatto il delete
    for(int i = 0;i < 10;i++)
        pthread_join(threads[i],NULL);

    //thread con parametri di ingresso

    //questo thread aspetta la conclusione di tutti gli altri thread figli
    //il secondo paramentro serve per far ritornare qualcosa dal thread
    pthread_join(pid,NULL);
  

    return 0;
}