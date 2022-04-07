package com.pier.book_register;

import com.pier.book_register.model.UserHandler;
import com.pier.book_register.view.SceneHandler;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class BookApplication extends Application {
    @Override
    public void start(Stage stage) {
        SceneHandler.getInstance().init(stage);
        UserHandler.getInstance().init();
    }

    public static void main(String[] args) {
        launch(args);
    }
}