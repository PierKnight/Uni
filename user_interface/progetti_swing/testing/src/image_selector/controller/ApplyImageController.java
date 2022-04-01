package image_selector.controller;

import image_selector.view.ImageInfo;
import image_selector.view.ImageViewerPanel;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class ApplyImageController extends MouseAdapter {

    private final ImageViewerPanel imageViewerPanel;
    private final Image image;

    public ApplyImageController(ImageInfo imageInfo,ImageViewerPanel imageViewerPanel) {
        this.imageViewerPanel = imageViewerPanel;
        this.image = imageInfo.getImage();
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        super.mouseClicked(e);
        this.imageViewerPanel.updateBackground(this.image);
    }
}
