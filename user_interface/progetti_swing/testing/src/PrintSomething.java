import java.io.*;
import java.util.Random;
import java.util.Scanner;

public class PrintSomething {


    public static void main(String[] args)
    {






        Random random = new Random();
        String path = "src/resources/file.txt";

        Scanner scanner = new Scanner(System.in);

        System.out.print("Write Matrix To file: ");


        while(scanner.hasNext()) {
            if (scanner.nextBoolean()) {
                try {
                    FileOutputStream out = new FileOutputStream(path);
                    System.out.print("Inserire Grandezza matrice: ");
                    int side = scanner.nextInt();

                    int totBytes = (int)Math.ceil(side * side / 8.0);

                    byte[] bytes = new byte[totBytes];
                    for(int i = 0;i < totBytes;i++)
                        bytes[i] = (byte) random.nextInt(256);

                    out.write(bytes);
                    out.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    FileInputStream in = new FileInputStream(path);
                    for(byte b : in.readAllBytes())
                        readByte(b);
                    in.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    private static void readByte(byte b)
    {
        for(int i = 7;i >= 0;i--)
        {
            System.out.print((b >> i & 1) == 1 ? "#" : "-");
        }

    }
}
