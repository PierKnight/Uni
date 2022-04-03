package snake.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class MainView {

    //initialize main frame
    public static void init()
    {
        JFrame frame = new JFrame("SNAKE GAME!");


        JOptionPane.showMessageDialog(frame,
                        "Premi Q per chiudere dal gioco in qualsiasi momento" + System.lineSeparator() +
                        "Premi freccia sinistra per muoverti a sinistra" + System.lineSeparator() +
                        "Premi freccia destra per muoverti a destra" + System.lineSeparator() +
                        "Premi freccia su per muoverti sopra" + System.lineSeparator() +
                        "Premi freccia già per muoverti giù" + System.lineSeparator()
                ,"Snake Inputs",JOptionPane.INFORMATION_MESSAGE);


        GamePanel gamePanel = new GamePanel();
        gamePanel.requestFocus();
        gamePanel.setFocusable(true);
        frame.add(gamePanel);
        frame.setSize(500,500);
        frame.setMinimumSize(frame.getSize());
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);
        frame.setUndecorated();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }
}
