package image_selector.view;

import image_selector.controller.ChooseImageController;

import javax.swing.*;
import java.awt.*;

public class ProgramMain {

    public static void main(String[] args) {


        JFrame jFrame = new JFrame();



        JPanel selectorPanel = new JPanel();
        selectorPanel.setLayout(new BoxLayout(selectorPanel,BoxLayout.Y_AXIS));


        JScrollPane scrollPane = new JScrollPane(selectorPanel);
        ImageViewerPanel viewerPanel = new ImageViewerPanel();
        viewerPanel.setBackground(Color.green);


        Button button = new Button("INSERISCI IMMAGINE");
        selectorPanel.add(button);
        button.addActionListener(new ChooseImageController(selectorPanel,viewerPanel));


        JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,scrollPane,viewerPanel);
        splitPane.setDividerSize(10);
        splitPane.setDividerLocation(100);
        splitPane.setOneTouchExpandable(true);
        splitPane.setContinuousLayout(true);




        jFrame.add(splitPane);
        jFrame.setSize(800, 800);
        jFrame.setMinimumSize(new Dimension(400, 400));
        jFrame.setVisible(true);
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);



    }
}
