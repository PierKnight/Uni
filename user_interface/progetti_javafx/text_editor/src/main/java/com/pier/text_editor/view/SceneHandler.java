package com.pier.text_editor.view;

import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;

public class SceneHandler {

    private static final SceneHandler instance = new SceneHandler();

    public static SceneHandler getInstance() {
        return instance;
    }
    ButtonType ok = new ButtonType("Queen");
    ButtonType rook = new ButtonType("Rook");



    public Alert showAlert(String title, String description, Alert.AlertType alertType)
    {
        Alert alert = new Alert(alertType,description);
        alert.setTitle(title);
        alert.showAndWait();
        return alert;
    }
}
