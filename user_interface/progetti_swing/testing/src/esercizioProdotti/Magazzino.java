package esercizioProdotti;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Magazzino {
    private final List<Prodotto> prodotti = new ArrayList<>();


    public boolean addProdotto(Prodotto prodotto)
    {
        if(!this.prodotti.contains(prodotto)) {
            this.prodotti.add(prodotto);
            return true;
        }
        return false;
    }

    public void clearAll()
    {
        this.prodotti.clear();
    }

    public boolean removeProdotto(String id)
    {
        return this.prodotti.removeIf(prodotto -> prodotto.getId().equals(id));
    }

    public List<Prodotto> cercaPerTipo(String tipo,SearchType searchType)
    {
        //nice name intellij I love it
        List<Prodotto> prodottos = new ArrayList<>();
        for(Prodotto prodotto : prodotti) {
            String stringSearch = searchType == SearchType.MARCA ? prodotto.getMarca() : (searchType == SearchType.MODELLO ? prodotto.getModello() : String.valueOf(prodotto.getAnno()));
            if (stringSearch.equals(tipo))
                prodottos.add(prodotto);
        }
        return prodottos;
    }

    public void stampaTuttiIProdotti()
    {
        System.out.println("Tutti i prodotti del magazzino: ");
        for(Prodotto prodotto : prodotti)
            System.out.println(prodotto);
    }

    public void ordinaPrezzoCrescente()
    {
        this.prodotti.sort(Comparator.comparingDouble(Prodotto::getPrezzo));
    }

    public void ordinaPrezzoDecrescente()
    {
        this.prodotti.sort((o1, o2) -> -Double.compare(o1.getPrezzo(),o2.getPrezzo()));
    }

    public static final String path = "src" + File.separator + "resources"  + File.separator;



    public void readProdotti(String fileName) throws IOException {

            List<String> stringProducts = Files.readAllLines(Path.of(path + fileName + ".txt"));
            for(String sProduct : stringProducts)
                this.addProdotto(Prodotto.newProdottoDaStringa(sProduct));


    }

    public void saveProdotti(String fileName) throws IOException
    {

        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(path + fileName + ".txt"));
        for(Prodotto prodotto : this.prodotti) {
            bufferedWriter.write(prodotto.saveString());
            bufferedWriter.newLine();
        }
        bufferedWriter.close();


    }

    public static enum SearchType
    {
        MARCA("MARCA", 0),
        MODELLO("MODELLO", 1),
        ANNO("ANNO", 2);

        public final String nome;
        public final int id;

        SearchType(String nome, int id) {
            this.nome = nome;
            this.id = id;
        }
    }
}
