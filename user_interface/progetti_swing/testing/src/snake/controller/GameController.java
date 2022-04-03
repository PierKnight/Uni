package snake.controller;

import snake.view.GamePanel;

import javax.swing.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class GameController extends KeyAdapter {

    private final GamePanel gamePanel;

    public GameController(GamePanel gamePanel) {
        this.gamePanel = gamePanel;
    }

    @Override
    public void keyPressed(KeyEvent e) {

        switch (e.getKeyCode())
        {
            //if player presses Q to exit
            case KeyEvent.VK_Q -> {
                int result = JOptionPane.showConfirmDialog(this.gamePanel, "Sei sicuro di voler uscire?", "ATTENZIONE", JOptionPane.YES_NO_CANCEL_OPTION);
                if (result == JOptionPane.OK_OPTION)
                    System.exit(0);
            }
        }
    }
}
