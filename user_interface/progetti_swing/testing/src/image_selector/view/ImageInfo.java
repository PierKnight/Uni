package image_selector.view;


import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class ImageInfo extends JLabel {
    private final BufferedImage  image;
    private final Image resizeImage;
    private final String name;

    public ImageInfo(BufferedImage image, String name) {
        this.image = image;
        this.resizeImage = this.image.getScaledInstance(50,50,Image.SCALE_SMOOTH);
        this.name = name;
        this.setIcon(new ImageIcon(resizeImage));
        this.setText(name);
        this.setIconTextGap(0);
    }

    public Image getImage() {
        return image;
    }

    public String getName() {
        return name;
    }
}
