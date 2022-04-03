package snake.view;

import snake.controller.GameController;

import javax.swing.*;
import java.awt.*;

public class GamePanel extends JPanel {

    public GamePanel()
    {

        this.addKeyListener(new GameController(this));
        this.setMinimumSize(new Dimension(500,500));
        this.setBackground(Color.red);


    }
}
