package esercizio17_03;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.regex.Pattern;

public class EspressioniRegolariEse {

    private static final char[] letters = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    private static final int[] numbers = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    private static final String path = "src" + File.separator + "resources" + File.separator;
    private final Random random = new Random();


    public static void main(String[] args) {
        EspressioniRegolariEse espressioniRegolari = new EspressioniRegolariEse();
        espressioniRegolari.stampaLineeConNumeroUguale("test.txt", 'a', 'b');
    }


    private String generateRandomString() {
        StringBuilder builder = new StringBuilder();


        int randomLength = 1 + random.nextInt(6);


        for (int i = 0; i < randomLength; i++) {
            String randomChar = random.nextBoolean() ? String.valueOf(letters[random.nextInt(letters.length)]) : String.valueOf(numbers[random.nextInt(numbers.length)]);
            builder.append(randomChar);
        }


        return builder.toString();


    }


    public void generaFile(String nomeFile) {


        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(path + nomeFile));

            int randomStrings = 4 + new Random().nextInt(10);

            for (int i = 0; i < randomStrings; i++) {
                writer.write(generateRandomString());
                writer.newLine();
            }

            writer.close();
        } catch (IOException e) {
            System.out.println("Qualcosa è andato storto con la scrittura del file: " + nomeFile);
        }
    }


    public List<String> leggiFile(String nomeFile) {


        List<String> strings = new ArrayList<>();

        try {
            BufferedReader reader = new BufferedReader(new FileReader(path + nomeFile));
            while (reader.ready())
                strings.add(reader.readLine());
            reader.close();
        } catch (IOException e) {
            System.out.println("Qualcosa è andato storto con la lettura del file: " + nomeFile);
        }
        return strings;
    }


    private static final Pattern NUMBER_PATTERN = Pattern.compile("[1-9]+");
    private static final Pattern ONE_NUMBER_PATTERN = Pattern.compile("([a-zA-Z]*(\\d)+[a-zA-Z]*)*");

    //uso le espressioni regolari per identificare le stringhe composte da soli numeri

    //la R alla fine del metodo indica che utilizza le espressioni regolari
    public void stampaLineeNumericheR(String nomeFile) {

        for (String string : leggiFile(nomeFile)) {
            if (NUMBER_PATTERN.matcher(string).matches())
                System.out.println(string);
        }
    }

    public void stampaLineeNumeriche(String nomeFile) {

        for (String string : leggiFile(nomeFile)) {

            boolean valid = true;
            for (int i = 0; i < string.length() && valid; i++)
                if (!Character.isDigit(string.charAt(i)))
                    valid = false;
            if (valid)
                System.out.println(string);
        }
    }

    public void stampaLineeConNumero(String nomeFile) {

        for (String string : leggiFile(nomeFile)) {
            if (ONE_NUMBER_PATTERN.matcher(string).matches())
                System.out.println(string);
        }
    }

    public void stampaLineeConLetterePari(String nomeFile, char lettera) {
        Pattern oneLetterPattern = Pattern.compile(lettera + "+");

        for (String string : leggiFile(nomeFile)) {
            if (string.length() % 2 == 0 && oneLetterPattern.matcher(string).matches())
                System.out.println(string);
        }
    }

    public void stampaLineeConNumeroUguale(String nomeFile, char lettera1, char lettera2) {


        for (String string : leggiFile(nomeFile)) {
            int total = 0;
            for (int i = 0; i < string.length(); i++) {
                if (lettera1 == string.charAt(i))
                    total += 1;
                else if (lettera2 == string.charAt(i))
                    total -= 1;
            }
            if (total == 0)
                System.out.println(string);
        }
    }

}
