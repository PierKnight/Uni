package image_selector.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class ImageViewerPanel extends JPanel {


    private Image image = null;

    public void updateBackground(Image image)
    {
        this.image = image;
        this.repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if(this.image != null)
            g.drawImage(this.image.getScaledInstance(getWidth(),getHeight(),Image.SCALE_SMOOTH),0,0,null);
    }
}
