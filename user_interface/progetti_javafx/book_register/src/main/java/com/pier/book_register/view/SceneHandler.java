package com.pier.book_register.view;

import com.pier.book_register.BookApplication;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.text.Font;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;

public class SceneHandler {

    private static final SceneHandler handler = new SceneHandler();

    public static SceneHandler getInstance() {
        return handler;
    }

    private Stage stage;
    private Scene scene;
    private String light_mode_style;
    private String dark_mode_style;

    private String currentLightStyle;

    public void init(Stage stage) {
        if (this.stage == null) {

            this.light_mode_style = BookApplication.class.getResource("css/light_mode.css").toExternalForm();
            this.dark_mode_style = BookApplication.class.getResource("css/dark_mode.css").toExternalForm();
            this.currentLightStyle = this.light_mode_style;
            this.stage = stage;
            this.stage.setTitle("Login Book Registry");
            createLoginScene();
            this.stage.setScene(scene);
            this.stage.show();
        }
    }

    public void switchLightMode()
    {
        if(this.currentLightStyle.equals(this.light_mode_style))
            this.currentLightStyle = this.dark_mode_style;
        else
            this.currentLightStyle = this.light_mode_style;

        if(this.scene != null) {
            if(this.scene.getStylesheets().isEmpty())
                this.scene.getStylesheets().add(this.currentLightStyle);
            else
                this.scene.getStylesheets().set(0,this.currentLightStyle);
        }
    }

    private <T> T loadRootFromFXML(String resourceName) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(SceneHandler.class.getResource(resourceName));
        return fxmlLoader.load();
    }

    public void createLoginScene() {
        try {
            if(scene == null) {
                scene = new Scene(loadRootFromFXML("login_view.fxml"));
                scene.getStylesheets().add(this.currentLightStyle);
            }
            else {
                scene.setRoot(loadRootFromFXML("login_view.fxml"));
            }

            stage.setMinWidth(400);
            stage.setMinHeight(300);
            stage.setWidth(400);
            stage.setHeight(300);
        } catch (IOException exception) {
            System.out.println("Qualcosa è andato storto con il caricamento della pagina login!");
        }
    }

    public void createBooksScene() {
        try {
            scene.setRoot(loadRootFromFXML("book_view.fxml"));
            stage.setMinWidth(400);
            stage.setMinHeight(300);
            stage.setWidth(400);
            stage.setHeight(300);
        } catch (IOException exception) {
            System.out.println("Qualcosa è andato storto con il caricamento della pagina books!");
        }
    }

    public void openCreateBookStage() {

        try {
            Stage stage = new Stage();
            stage.onCloseRequestProperty().addListener(new ChangeListener<EventHandler<WindowEvent>>() {
                @Override
                public void changed(ObservableValue<? extends EventHandler<WindowEvent>> observableValue, EventHandler<WindowEvent> windowEventEventHandler, EventHandler<WindowEvent> t1) {
                    System.out.println("eeeee");
                }
            });

            stage.initModality(Modality.APPLICATION_MODAL);
            stage.setTitle("Register new book");
            stage.setMinHeight(400);
            stage.setMinWidth(500);
            stage.setWidth(500);
            stage.setHeight(400);
            stage.setMaxHeight(400);
            Scene scene = new Scene(loadRootFromFXML("new_book_view.fxml"));
            scene.getStylesheets().add(this.currentLightStyle);
            stage.setScene(scene);
            stage.show();
        }
        catch (IOException e) {
            System.out.println("Qualcosa è andato storto con il caricamento della pagina add new book!");
        }
    }


    public void createAlertMessage(String title, String message, Alert.AlertType alertType) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        //alert.setContentText(message);
        alert.getDialogPane().getStylesheets().addAll(this.scene.getStylesheets());

        TextArea area = new TextArea(message);
        area.setFont(Font.font("verdana",18));
        area.setWrapText(true);
        area.setEditable(false);
        alert.getDialogPane().setContent(area);
        alert.show();
    }

    public void createErrorMessage(String message)
    {
        this.createAlertMessage("ERROR!",message, Alert.AlertType.ERROR);
    }

}
