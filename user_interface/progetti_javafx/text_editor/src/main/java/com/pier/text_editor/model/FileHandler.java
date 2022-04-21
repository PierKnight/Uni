package com.pier.text_editor.model;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.control.Tab;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

public class FileHandler {
    private static final FileHandler instance = new FileHandler();

    public final ObjectProperty<SingleSelectionModel<Tab>> selectedTab = new SimpleObjectProperty<>();

    private FileHandler()
    {
    }

    public static FileHandler getInstance() {
        return instance;
    }

    private final Map<String,EditFile> loadedFiles = new HashMap<>();

    private int totalNewPages = 0;


    public EditFile addNewEditFile() {
        EditFile newFile = new EditFile();
        loadedFiles.put(newFile.getPath(), newFile);
        return newFile;

    }

    public EditFile openFile()
    {
        FileChooser fileChooser = new FileChooser();

        File file = fileChooser.showOpenDialog(null);

        if(file == null)
            return null;


        try {
            EditFile editFile = new EditFile(file.getName(), Files.readString(Path.of(file.getAbsolutePath())),file.getAbsolutePath());
            loadedFiles.put(file.getAbsolutePath(),editFile);
            return editFile;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void saveFile()
    {
        EditFile selectedFile = getEditFile(this.selectedTab.get().getSelectedItem());
        if(selectedFile == null)
            return;


        if(selectedFile.isNewFile())
        {
            FileChooser fileChooser = new FileChooser();
            File file = fileChooser.showSaveDialog(null);
            if(file != null)
            {
                this.loadedFiles.remove(selectedFile.getPath());
                selectedFile.completeFile(file.getName(),getTextArea(this.selectedTab.get().getSelectedItem()).getText(),file.getAbsolutePath());
                this.loadedFiles.put(file.getAbsolutePath(),selectedFile);
                this.selectedTab.get().getSelectedItem().setText(file.getName());
            }
        }

        try {
            Files.writeString(Path.of(selectedFile.getPath()),getTextArea(this.selectedTab.get().getSelectedItem()).getText());
        } catch (IOException e) {
            e.printStackTrace();
        }

    }



    public EditFile getEditFile(Tab tab)
    {
        if(tab != null)
            return this.loadedFiles.get(tab.getId());
        return null;
    }

    public TextArea getTextArea(Tab tab)
    {
        if(tab != null)
            return (TextArea) tab.getContent();
        return null;
    }


    public boolean isFileEdited(Tab tab)
    {
        EditFile file = getEditFile(tab);
        TextArea textArea = getTextArea(tab);

        if(file != null && file.isNewFile())
            return true;


        return file != null && textArea != null && !file.getContent().equals(textArea.getText());
    }




}
