package com.pier.book_register.model;

import java.util.Objects;

public record Book(String isbn, String title, String author, String publisher, String year) {
    @Override
    public String toString() {
        return isbn + "," + title  + "," + author + "," + publisher + "," + year;
    }
}
