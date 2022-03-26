import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EspressioniRegolari {


    public static void main(String[] args) {


        //test 1: true se è un indirizzo di email valido,
        //dominio è composto da due lettere alfabeto minuscole
        //Pattern pattern = Pattern.compile("([a-zA-Z]+)@unical\\.([a-z]{2})");


        Pattern pattern = Pattern.compile("([a-zA-Z]*(\\d)+[a-zA-Z]*)*");


        Scanner scanner = new Scanner(System.in);


        String input = scanner.nextLine();

        while (!input.equalsIgnoreCase("s")) {

            Matcher matcher = pattern.matcher(input);
            if (matcher.matches()) {
                System.out.println("La stringa \"" + input + "\" è valida");
                System.out.println("Gruppi totali: " + matcher.groupCount());

                for (int i = 0; i < matcher.groupCount(); i++)
                    System.out.println(matcher.group(i + 1));

            } else
                System.out.println("Fuck");
            input = scanner.nextLine();
        }


    }
}
