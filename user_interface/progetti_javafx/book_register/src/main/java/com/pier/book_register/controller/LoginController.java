package com.pier.book_register.controller;

import com.pier.book_register.model.UserHandler;
import com.pier.book_register.view.SceneHandler;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

public class LoginController {

    @FXML
    private Button loginButton;

    @FXML
    private PasswordField passwordField;

    @FXML
    private TextField usernameField;

    @FXML
    void onLoginPressed(ActionEvent event) {

        UserHandler userHandler = UserHandler.getInstance();
        //if(userHandler.tryToLogin(usernameField.getText(),passwordField.getText()))
        if(userHandler.tryToLogin("username1","password1")) //debug only
            SceneHandler.getInstance().createBooksScene();
        else
            SceneHandler.getInstance().createErrorMessage("Username o Password errate!");


    }

}
