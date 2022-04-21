package com.pier.text_editor.controller;

import com.pier.text_editor.model.EditFile;
import com.pier.text_editor.model.FileHandler;
import com.pier.text_editor.view.SceneHandler;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TextArea;

import java.io.File;

public class MainController {

    @FXML
    private TabPane tabPane;


    @FXML
    public void initialize()
    {
        FileHandler.getInstance().selectedTab.bind(this.tabPane.selectionModelProperty());
    }

    @FXML
    void onNewPressed(ActionEvent event) {
        createNewFileEditor(FileHandler.getInstance().addNewEditFile());
    }

    @FXML
    void onOpenPressed(ActionEvent event) {

        EditFile file = FileHandler.getInstance().openFile();

        if(file != null)
            createNewFileEditor(file);

    }

    @FXML
    void onSavePressed(ActionEvent event) {
        FileHandler.getInstance().saveFile();
    }



    private void createNewFileEditor(EditFile editFile)
    {

        Tab tab = new Tab(editFile.getFileName());
        tab.setId(editFile.getPath());
        tab.setClosable(true);

        TextArea textArea = new TextArea();
        textArea.setPromptText("Inserire testo qui");
        textArea.setText(editFile.getContent());
        textArea.textProperty().addListener((observable, oldValue, newValue) -> {
            if(FileHandler.getInstance().isFileEdited(tab))
                tab.setText("*" + editFile.getFileName());
            else
                tab.setText(editFile.getFileName());
        });

        tab.setOnCloseRequest(new EventHandler<Event>() {
            @Override
            public void handle(Event event) {
                if(FileHandler.getInstance().isFileEdited(tab))
                {
                    Alert closeAlert = SceneHandler.getInstance().showAlert("WARNING", editFile.getFileName() + " is not saved!", Alert.AlertType.CONFIRMATION);
                    if(closeAlert.getResult() == closeAlert.getButtonTypes().get(1))
                        event.consume();
                }
            }
        });

        tab.setContent(textArea);
        tabPane.getTabs().add(tab);

    }

}
