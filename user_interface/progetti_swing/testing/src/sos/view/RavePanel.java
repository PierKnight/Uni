package sos.view;

import sos.controller.Inputs;
import sos.model.RaveHandler;

import javax.swing.*;
import java.awt.*;

public final class RavePanel extends JPanel {

    public Color color = Color.RED;

    public RavePanel()
    {
        this.addMouseListener(new Inputs(this));
        RaveHandler.getInstance().initPanel(this);
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.setColor(color);

        g.drawLine(0,0,this.getWidth(),getHeight());
    }
}
