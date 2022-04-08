package com.pier.book_register.model;

public class User
{
    private final String username;
    private final String password;
    private final BookManager bookManager;


    public User(String username, String password) {
        this.username = username;
        this.password = password;
        this.bookManager = new BookManager();
    }

    public String getUsername() {
        return username;
    }

    public BookManager getBookManager() {
        return bookManager;
    }
}
