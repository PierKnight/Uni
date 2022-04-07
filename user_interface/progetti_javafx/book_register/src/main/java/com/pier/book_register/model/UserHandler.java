package com.pier.book_register.model;

import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class UserHandler {

    private static final UserHandler handler = new UserHandler();

    public static UserHandler getInstance() {
        return handler;
    }

    private User loggedUser = null;
    private Map<String,User> userDataBase = new HashMap<>();

    public void init()
    {
        try {
            List<String> lines = Files.readAllLines(Paths.get(UserHandler.class.getResource("users.data").toURI()));

            for (String line : lines) {

                String[] split = line.split(";");
                if(split.length != 2)
                    continue;
                String username = split[0];
                if(this.userDataBase.containsKey(username))
                    continue;
                this.userDataBase.put(username,new User(username,split[1]));
            }


        } catch (IOException | URISyntaxException e) {
            System.out.println("Something Went wrong while reading users file");
        }
    }

    public boolean tryToLogin(String username,String password)
    {
        User user = this.userDataBase.get(username);
        if(user != null)
        {
            this.loggedUser = user;
            return true;
        }
        return false;
    }

    public void logout()
    {
        this.loggedUser = null;
    }


    public User getLoggedUser() {
        return loggedUser;
    }

    //get all registed users, THE RETURNED Collection IS IMMUTABLE
    public Collection<User> getRegisteredUsers()
    {
        return Collections.unmodifiableCollection(this.userDataBase.values());
    }
}
