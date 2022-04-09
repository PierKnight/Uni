package com.pier.book_register.model;

import java.util.Objects;

public record Book(String isbn, String title, String author, String publisher, String year) {


    @Override
    public String toString() {
        return isbn + ";" + title  + ";" + author + ";" + publisher + ";" + year;
    }

    public static Book readFromString(String string)
    {
        String[] split = string.split(";");
        if(split.length != 5)
            return null;
        return new Book(split[0],split[1],split[2],split[3],split[4]);
    }
}
