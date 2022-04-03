package image_selector.controller;

import image_selector.view.ImageInfo;
import image_selector.view.ImageViewerPanel;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ChooseImageController implements ActionListener {

    private static final FileNameExtensionFilter IMAGE_FILTER = new FileNameExtensionFilter("Image files", ImageIO.getReaderFileSuffixes());

    private final JPanel selectorPanel;
    private final ImageViewerPanel imageViewerPanel;

    public ChooseImageController(JPanel selectorPanel, ImageViewerPanel imageViewerPanel) {
        this.selectorPanel = selectorPanel;
        this.imageViewerPanel = imageViewerPanel;
    }


    @Override
    public void actionPerformed(ActionEvent e) {


        JFileChooser fileChooser = new JFileChooser();
        fileChooser.addChoosableFileFilter(IMAGE_FILTER);
        int res = fileChooser.showOpenDialog(null);

        if(res != JFileChooser.APPROVE_OPTION)
            return;

        File file = fileChooser.getSelectedFile();

        if(!IMAGE_FILTER.accept(file)) {
            JOptionPane.showMessageDialog(null, file.getName(), "Invalid File Image", JOptionPane.ERROR_MESSAGE);
            return;
        }

        try {
            BufferedImage image = ImageIO.read(file);
            String selectName = JOptionPane.showInputDialog("Inserisci nome dell'immagine");

            if(selectName == null)
                return;

            ImageInfo imageInfo = new ImageInfo(image,selectName);
            selectorPanel.add(imageInfo);
            selectorPanel.repaint();
            selectorPanel.revalidate();
            imageInfo.addMouseListener(new ApplyImageController(imageInfo,imageViewerPanel));



        } catch (IOException ex) {
        }






    }
}
