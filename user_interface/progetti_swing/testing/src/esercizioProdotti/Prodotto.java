package esercizioProdotti;

import java.util.Objects;

public class Prodotto {
    private final String id;
    private final String tipo;
    private final String marca;
    private final String modello;
    private final int anno;
    private final double prezzo;

    public Prodotto(String id, String tipo, String marca, String modello, int anno, double prezzo) throws IllegalArgumentException {
        this.id = id;
        this.tipo = tipo;
        this.marca = marca;
        this.modello = modello;
        this.anno = anno;
        this.prezzo = prezzo;

        if(this.anno < 1900 || this.anno > 2050)
            throw new IllegalArgumentException("Minimo Anno 1900, Massimo Anno 2050, ottenuto: " + anno);

        if(this.prezzo < 0.0D)
            throw new IllegalArgumentException("Minimo Prezzo 0.0D, ottenuto: " + prezzo);

    }

    public String getId() {
        return id;
    }

    public String getTipo() {
        return tipo;
    }

    public String getMarca() {
        return marca;
    }

    public String getModello() {
        return modello;
    }

    public int getAnno() {
        return anno;
    }

    public double getPrezzo() {
        return prezzo;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Prodotto prodotto = (Prodotto) o;

        Objects.requireNonNull(prodotto.id);

        return this.id.equals(prodotto.id);
    }

    @Override
    public int hashCode() {
        return this.id.hashCode();
    }

    @Override
    public String toString() {
        return "Prodotto{" +
                "id='" + id + '\'' +
                ", tipo='" + tipo + '\'' +
                ", marca='" + marca + '\'' +
                ", modello='" + modello + '\'' +
                ", anno=" + anno +
                ", prezzo=" + prezzo +
                '}';
    }


    public static Prodotto newProdottoDaStringa(String string) throws IllegalArgumentException {
        String[] elementi = string.split(";");
        if(elementi.length != 6)
            throw new IllegalArgumentException("Numero di argomenti invalidi! deve essere 6 invece è " + elementi.length);

        return new Prodotto(elementi[0],elementi[1],elementi[2],elementi[3],Integer.parseInt(elementi[4]),Double.parseDouble(elementi[5]));
    }

    public String saveString()
    {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(id);
        stringBuilder.append(";");
        stringBuilder.append(tipo);
        stringBuilder.append(";");
        stringBuilder.append(marca);
        stringBuilder.append(";");
        stringBuilder.append(modello);
        stringBuilder.append(";");
        stringBuilder.append(anno);
        stringBuilder.append(";");
        stringBuilder.append(prezzo);
        return stringBuilder.toString();
    }
}
