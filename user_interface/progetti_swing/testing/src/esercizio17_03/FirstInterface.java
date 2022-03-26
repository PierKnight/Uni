package esercizio17_03;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class FirstInterface {
    public static void main(String[] args) {


        JFrame frame = new JFrame("first frame");


        JPanel tab1 = new JPanel();

        tab1.setBackground(Color.blue);


        JTextArea textArea = new JTextArea();
        textArea.setPreferredSize(new Dimension(400, 400));
        textArea.setTabSize(3);
        textArea.setRows(30);
        textArea.setColumns(30);
        textArea.setLineWrap(true);
        textArea.addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                System.out.println("FOCUS");
            }
        });
        tab1.add(textArea);


        JPanel tab2 = new JPanel(new BorderLayout(5, 5));


        //creazione panello sinistro per il tab2
        JPanel leftPanel = new JPanel(new FlowLayout());

        JScrollPane scrollPane = new JScrollPane(leftPanel);
        leftPanel.setPreferredSize(new Dimension(200, 2 * 120));
        leftPanel.setBackground(Color.GREEN);

        for (int i = 0; i < 3; i++) {
            addNewPanel(leftPanel);
        }


        JPanel test = new JPanel(new GridLayout());
        test.setBackground(Color.CYAN);

        Button removeButton = new Button("REMOVE");
        removeButton.addActionListener(e -> {
            if (leftPanel.getComponents().length > 0) {
                leftPanel.remove(0);
                leftPanel.repaint();
            }
        });

        Button addButton = new Button("ADD");
        removeButton.addActionListener(e -> {
            JPanel pan = addNewPanel(leftPanel);
            leftPanel.repaint();
        });

        test.add(removeButton);
        test.add(addButton);

        tab2.add(test, BorderLayout.CENTER);

        tab2.add(scrollPane, BorderLayout.WEST);


        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Primo Tab", tab1);
        tabbedPane.addTab("Secondo Tab", tab2);
        frame.add(tabbedPane);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 400);
        frame.setVisible(true);
    }

    private static JPanel addNewPanel(JPanel addTo) {
        JPanel newPanel = new JPanel();
        newPanel.setPreferredSize(new Dimension(100, 100));
        newPanel.setBackground(Color.RED);
        newPanel.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                if (newPanel.getBackground() == Color.RED)
                    newPanel.setBackground(Color.BLUE);
                else
                    newPanel.setBackground(Color.RED);

            }
        });

        addTo.add(newPanel);
        return newPanel;
    }

}
