package com.unical.pier.firstese;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MainApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(MainApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 320);
        scene.getStylesheets().add(getClass().getResource("my-style.css").toExternalForm());
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.setMinHeight(320);
        stage.setMinWidth(320);
        stage.show();




    }

    public static void main(String[] args) {
        launch();
    }
}