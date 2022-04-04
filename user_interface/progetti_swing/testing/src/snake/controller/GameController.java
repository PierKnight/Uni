package snake.controller;

import snake.model.Game;
import snake.model.Options;
import snake.view.SnakePanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class GameController extends KeyAdapter {

    private final SnakePanel gamePanel;

    public GameController(SnakePanel gamePanel) {
        this.gamePanel = gamePanel;
    }

    @Override
    public void keyPressed(KeyEvent e) {


        Game game = Game.getInstance();
        Point direction = null;
        switch (e.getKeyCode())
        {

            //if player presses Q to exit
            case KeyEvent.VK_Q -> {
                int result = JOptionPane.showConfirmDialog(this.gamePanel, "Sei sicuro di voler uscire?", "ATTENZIONE", JOptionPane.YES_NO_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION)
                    System.exit(0);
            }
            case KeyEvent.VK_RIGHT -> direction = Options.RIGHT;
            case KeyEvent.VK_LEFT -> direction = Options.LEFT;
            case KeyEvent.VK_UP -> direction = Options.UP;
            case KeyEvent.VK_DOWN -> direction = Options.DOWN;
        }
        if(direction != null)
        {
            //with this line the snake cannot walk backwards if it is longer than 1 piece
            if(game.getDirection().x == -direction.x && game.getDirection().y == -direction.y && game.getSnakeLength() > 1)
                return;
            game.setDirection(direction);
            game.moveSnake();
            this.gamePanel.repaint();
        }
    }
}
