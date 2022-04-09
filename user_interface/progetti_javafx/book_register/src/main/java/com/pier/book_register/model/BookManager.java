package com.pier.book_register.model;

import com.pier.book_register.view.SceneHandler;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class BookManager {


    private final ObservableList<Book> books = FXCollections.observableArrayList();

    public void addBook(Book book){
        this.books.add(book);
    }

    public ObservableList<Book> getBooks() {
        return books;
    }


    public void readFromFile(File file)
    {
        try {
            List<String> lines = Files.readAllLines(file.toPath());
            StringBuilder invalidLinesBuilder = new StringBuilder();

            for (int i = 0;i < lines.size();i++) {
                String string = lines.get(i);
                Book book = Book.readFromString(string);
                if(book != null)
                    this.books.add(book);
                else
                    invalidLinesBuilder.append("Invalid Book String \"").append(string).append("\" at line: ").append(i).append("\n");
            }
            if(!invalidLinesBuilder.isEmpty())
                SceneHandler.getInstance().createAlertMessage("WARNING: Invalid Strings",invalidLinesBuilder.toString(), Alert.AlertType.WARNING);

        } catch (IOException e) {
            SceneHandler.getInstance().createErrorMessage(e.getMessage());
        }
    }
}
