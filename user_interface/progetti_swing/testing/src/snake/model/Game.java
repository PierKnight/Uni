package snake.model;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Game {

    private static Game game = new Game();
    private final Tile[][] matrix = new Tile[Options.ROWS][Options.COLUMNS];

    private final LinkedList<Point> snake = new LinkedList<>();
    private Point direction = Options.RIGHT;
    private int eatenFruits = 0;
    private Random random = new Random();


    private Game()
    {
        for(int i = 0;i < Options.ROWS;i++)
        {
            for(int j = 0;j < Options.COLUMNS;j++)
            {
                if(i == 0 || i == Options.ROWS - 1 || j == 0 || j == Options.COLUMNS - 1)
                    matrix[i][j] = Tile.WALL;
                else
                    matrix[i][j] = Tile.EMPTY;
            }
        }

        this.snake.addFirst(new Point(1,1));
        this.matrix[1][1] = Tile.SNAKE;

        generateRandomFruit();
    }

    public Tile[][] getMatrix()
    {
        return matrix;
    }

    public void setDirection(Point direction)
    {
        this.direction = direction;
    }

    public Point getDirection() {
        return direction;
    }

    public int getEatenFruits() {
        return eatenFruits;
    }

    public int getSnakeLength()
    {
        return this.snake.size();
    }

    /*
                this method checks if the snake can move in that position and ,if so, do something about it
                return false means the snake cannot move in that slot.
             */
    private boolean snakeMoveListener(int x,int y)
    {
        if((x < 0 || x >= Options.ROWS) || (y < 0 || y >= Options.COLUMNS)) {
            System.out.println("WARNING THE SNAKE TRIED TO GO OUTSIDE THE MAP!!!");
            return false;
        }

        Tile tile = matrix[x][y];
        if(tile == Tile.WALL || tile == Tile.SNAKE) {
            this.endGame();
            return false;
        }
        if(tile == Tile.FRUIT) {
            generateRandomFruit();
            this.eatenFruits++;
        }
        return true;
    }


    public void moveSnake()
    {
        Point head = this.snake.getFirst();
        if(!this.snakeMoveListener(head.x + direction.x,head.y + direction.y))
            return;

        Point newHead = new Point(head.x + direction.x,head.y + direction.y);
        this.matrix[newHead.x][newHead.y] = Tile.SNAKE;
        this.snake.addFirst(newHead);

        if(eatenFruits == 0)
        {
            Point tail = this.snake.removeLast();
            this.matrix[tail.x][tail.y] = Tile.EMPTY;
        }
        else
            this.eatenFruits--;
    }

    public void endGame()
    {
        game = new Game();
    }

    public void generateRandomFruit()
    {
        boolean found = false;
        int iterations = 0;
        while(!found)
        {
            int randX = random.nextInt(Options.ROWS);
            int randY = random.nextInt(Options.COLUMNS);

            if(this.matrix[randX][randY] == Tile.EMPTY)
            {
                this.matrix[randX][randY] = Tile.FRUIT;
                found = true;
            }
            iterations++;
        }


    }


















    public static Game getInstance() {
        return game;
    }


}
