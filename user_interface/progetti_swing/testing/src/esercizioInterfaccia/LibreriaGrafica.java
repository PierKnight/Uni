package esercizioInterfaccia;

public class LibreriaGrafica
{
    private int size = 0;
    private IDisegno[] disegni = new IDisegno[2];


    public void add(IDisegno disegno)
    {
        if(size >= disegni.length)
        {
            IDisegno[] tmp = new IDisegno[this.disegni.length * 2];
            for (int i = 0; i < disegni.length; i++)
                tmp[i] = disegni[i];
            disegni = tmp;
        }
        disegni[size++] = disegno;
    }

    public boolean remove(int index)
    {
        if(index >= this.size)
            return false;

        for (int i = index; i < this.size - 1; i++)
            this.disegni[i] = this.disegni[i + 1];
        this.size--;
        return true;
    }

    //rimuove dall' array dinamico il disegno presente nell'argomento paragonando se i riferimenti sono uguali
    public boolean remove(IDisegno disegno)
    {
        int foundDisegno = -1;
        for (int i = 0; i < this.size; i++)
            if(this.disegni[i] == disegno)
                foundDisegno = i;
        if(foundDisegno != -1)
        {
            remove(foundDisegno);
            return true;
        }
        return false;
    }

    public void stampaDisegni()
    {
        for (int i = 0; i < this.size; i++)
            this.disegni[i].disegna();
    }

    public int numDisegni()
    {
        return this.size;
    }


    public static void main(String[] args)
    {
        LibreriaGrafica libreriaGrafica = new LibreriaGrafica();
        Quadrato quadrato1 = new Quadrato(10);
        Rettangolo rettangolo = new Rettangolo(10,2);
        libreriaGrafica.add(quadrato1);
        libreriaGrafica.add(rettangolo);

        libreriaGrafica.remove(quadrato1);

        libreriaGrafica.stampaDisegni();

        System.out.println("Totale Disegni: " + libreriaGrafica.size);

    }
}
