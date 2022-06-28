package sos.controller;

import sos.view.RavePanel;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Inputs extends MouseAdapter {

    private final RavePanel panel;

    public Inputs(RavePanel panel)
    {
        this.panel = panel;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        System.out.println("SSOSOSOSOOSOSS" + panel.getMaximumSize());
    }
}
