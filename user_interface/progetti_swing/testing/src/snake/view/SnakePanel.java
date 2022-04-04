package snake.view;

import snake.controller.GameController;
import snake.model.Game;
import snake.model.Options;
import snake.model.Tile;

import javax.swing.*;
import java.awt.*;

public class SnakePanel extends JPanel {

    public SnakePanel()
    {
        this.addKeyListener(new GameController(this));
        this.setBackground(Color.white);
        this.setPreferredSize(new Dimension(Options.COLUMNS * Options.TILE_SIZE,Options.ROWS * Options.TILE_SIZE));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Game game = Game.getInstance();

        for(int i = 0;i < Options.ROWS;i++)
        {
            for(int j = 0;j < Options.COLUMNS;j++)
            {
                Tile tile = game.getMatrix()[i][j];

                switch (tile)
                {
                    case WALL -> {g.setColor(Color.BLACK); g.fillRect(i * Options.TILE_SIZE,j * Options.TILE_SIZE,Options.TILE_SIZE,Options.TILE_SIZE);}
                    case SNAKE -> {g.setColor(Color.green); g.fillRect(i * Options.TILE_SIZE,j * Options.TILE_SIZE,Options.TILE_SIZE,Options.TILE_SIZE);}
                    case FRUIT -> {g.setColor(Color.red); g.fillRect(i * Options.TILE_SIZE,j * Options.TILE_SIZE,Options.TILE_SIZE,Options.TILE_SIZE);}
                }

            }
        }

    }
}
