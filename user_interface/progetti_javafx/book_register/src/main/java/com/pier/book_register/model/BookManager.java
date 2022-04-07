package com.pier.book_register.model;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.util.ArrayList;

public class BookManager {


    private final ObservableList<Book> books = FXCollections.observableArrayList();

    public void addBook(Book book){
        this.books.add(book);
    }

    public ObservableList<Book> getBooks() {
        return books;
    }
}
