package sos.model;

import sos.view.RavePanel;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public final class RaveHandler {

    private static RaveHandler handler = new RaveHandler();


    public static RaveHandler getInstance() {
        return handler;
    }

    private final ScheduledExecutorService executorService = Executors.newSingleThreadScheduledExecutor();
    private RavePanel panel = null;

    private RaveHandler()
    {
        Random random = new Random();

        executorService.scheduleAtFixedRate(() -> {
            if(panel != null)
                SwingUtilities.invokeLater(() ->
                {
                    panel.color = Color.getHSBColor(random.nextFloat(), random.nextFloat(), random.nextFloat());
                    panel.repaint();
                });
        },0,1, TimeUnit.SECONDS);
    }


    public void initPanel(RavePanel ravePanel)
    {
        this.panel = ravePanel;

    }


}
