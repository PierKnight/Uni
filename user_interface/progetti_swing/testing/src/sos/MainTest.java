package sos;

import sos.view.RavePanel;

import javax.swing.*;
import java.awt.*;

public class MainTest {
    public static void main(String[] args) {
        JFrame jFrame = new JFrame("ee");
        jFrame.setSize(500,500);



        RavePanel panel = new RavePanel();



        panel.setBackground(Color.red);
        panel.setPreferredSize(new Dimension(200,200));
        panel.setMaximumSize(new Dimension(300,300));
        jFrame.add(panel,BorderLayout.WEST);


        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jFrame.setVisible(true);
    }
}
