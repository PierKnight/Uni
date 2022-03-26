package esercizioProdotti;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

public class Main {

    private static final Comando[] COMANDI = Comando.values();
    private static final Magazzino magazzino = new Magazzino();


    private static final Path DEFAULT_PATH = Path.of(Magazzino.path + "default_file.txt");

    public static void main(String[] args) {


        Scanner scanner = new Scanner(System.in);




        try {
            magazzino.readProdotti(Files.readString(DEFAULT_PATH));
        } catch (IOException e) {
            System.out.println("Qualcosa è andato storto con il carimento default del file!");
        }


        System.out.println("----Comandi");
        for(Comando comando : COMANDI)
            comando.printComando();
        System.out.println(COMANDI.length + " - CHIUDI TERMINALE");


        int commandID = scanner.nextInt();

        while(commandID < COMANDI.length)
        {
            commandHandler(scanner,COMANDI[commandID]);

            commandID = scanner.nextInt();
        }
    }


    private static void commandHandler(Scanner scanner,Comando comando) {
        switch (comando)
        {
            case AGGIUNGI ->
                    {
                        System.out.println("Inserire ID: ");
                        String id = scanner.next();
                        System.out.println("Inserire Tipo: ");
                        String tipo = scanner.next();
                        System.out.println("Inserire Marca: ");
                        String marca = scanner.next();
                        System.out.println("Inserire Modello: ");
                        String modello = scanner.next();
                        System.out.println("Inserire Anno: ");
                        int anno = scanner.nextInt();
                        System.out.println("Inserire Prezzo: ");
                        double prezzo = scanner.nextDouble();
                        magazzino.addProdotto(new Prodotto(id,tipo,marca,modello,anno,prezzo));
                        System.out.println("Inserito Prodotto Con Successo");
                    }
            case RIMUOVI -> {
                System.out.println("Inserire Prodotto Da rimuovoere");
                String id = scanner.next();
                if(magazzino.removeProdotto(id))
                    System.out.println("Rimosso con Successo");
                else
                    System.out.println("Rimozione non avvenuta");
            }
            case STAMPA_TUTTO -> {
                magazzino.stampaTuttiIProdotti();
            }
            case RICERCA -> {
                System.out.println("Inserire Tipologia Ricerca (0 Marca, 1 Modello, 2 Anno): ");
                Magazzino.SearchType searchType = Magazzino.SearchType.values()[scanner.nextInt()];
                System.out.println("Inserire " + searchType.nome + " da cercare:");

                String se = scanner.next();
                System.out.println("-Lista di prodotto con la "+ searchType.nome + ": " + se + "-");
                for(Prodotto prodotto : magazzino.cercaPerTipo(se,searchType))
                    System.out.println(prodotto);
            }
            case ORDINAMENTO -> {
                System.out.println("Ordinare In Maniera Crescente? Y/N");
                if(scanner.next().equalsIgnoreCase("Y")) {
                    magazzino.ordinaPrezzoCrescente();
                    System.out.println("Ordinato Con Criterio Crescente");
                }
                else {
                    magazzino.ordinaPrezzoDecrescente();
                    System.out.println("Ordinato Con Criterio Decrescente");
                }
            }
            case SALVA -> {
                System.out.println("Inserire Nome File: ");
                String fileName = scanner.next();
                try {
                    magazzino.saveProdotti(fileName);
                    System.out.println("Prodotti Salvati!");
                } catch (IOException e) {
                    System.out.println("Qualcosa E' Andato Storto nel saving!");
                }
            }
            case CARICA -> {
                System.out.println("Inserire Nome File: ");
                String fileName = scanner.next();
                try {
                    magazzino.readProdotti(fileName);
                    System.out.println("Prodotti Caricati!");
                } catch (IOException e) {
                    System.out.println("Qualcosa E' Andato Storto nel caricamento!");
                }
            }
            case DEFAULT_LOAD -> {
                System.out.println("Inserire Nome file di default");
                String default_file_name = scanner.next();
                try {
                    Files.writeString(DEFAULT_PATH,default_file_name);
                } catch (IOException e) {
                    System.out.println("Non è stato possibile salvare il default file.");
                    e.printStackTrace();
                }
            }
            case RIPULISCI -> {
                int confermeTotali = 0;

                StringBuilder builder = new StringBuilder();
                builder.append("(Y/S) MA SEI ");

                while(confermeTotali < 5)
                {
                    builder.append("SICURO?");
                    System.out.println(builder);
                    if(scanner.next().equalsIgnoreCase("Y"))
                        confermeTotali++;
                    else {
                        System.out.println("VISTO CHE CHIEDERE NON FA MALE?");
                        return;
                    }
                }
                System.out.println("I PRODOTTI SONO STATI RIPULITI!!");
                magazzino.clearAll();
            }
            default -> System.out.println("SE STAMPI QUESTO VUOL DIRE CHE IL COMANDO NON E' STATO IMPLEMENTATO!");
        }

    }

    public enum Comando
    {
        AGGIUNGI(0,"Aggiungi un nuovo Prodotto"),
        RIMUOVI(1,"Rimuovi un Prodotto"),
        STAMPA_TUTTO(2,"Stampa Tutti I prodotti"),
        RICERCA(3,"Stampa I prodotti per marca/modello/anno"),
        ORDINAMENTO(4,"Ordina I prodotti a seconda del prezzo"),
        RIPULISCI(5,"Ripulisce l'intero magazzino dei prodotti! (Meglio Avere un backup)"),
        SALVA(6,"Salva Tutti I Prodotti in un unico file."),
        CARICA(7,"Carica Prodotti Da file locale"),
        DEFAULT_LOAD(8,"Puoi definire un file che verrà caricato in automatico all'avvio di questo terminale");

        private final int id;
        private final String descrizione;

        Comando(int id, String descrizione)
        {
            this.id = id;
            this.descrizione = descrizione;
        }

        public int getId() {
            return id;
        }

        public String getDescrizione() {
            return descrizione;
        }

        public void printComando()
        {
            System.out.println(this.id + " - " + this.getDescrizione());
        }
    }

}
