package com.pier.book_register.controller;

import com.pier.book_register.model.Book;
import com.pier.book_register.model.UserHandler;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.Clipboard;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.net.URL;
import java.util.ResourceBundle;

public class AddBookController implements Initializable {

    @FXML
    private TextField ISBNTextField;

    @FXML
    private TextField authorTextField;

    @FXML
    private TextField publisherTextField;

    @FXML
    private TextField titleTextField;

    @FXML
    private TextField yearTextField;

    @FXML
    private Button pasteButton;

    @FXML
    void onAddBookPressed(ActionEvent event) {

        Book book = new Book(this.ISBNTextField.getText(),
                this.titleTextField.getText(),
                this.authorTextField.getText(),
                this.publisherTextField.getText(),
                this.yearTextField.getText());
        UserHandler.getInstance().getLoggedUser().getBookManager().addBook(book);
        Stage stage = (Stage) this.authorTextField.getScene().getWindow();
        stage.close();
    }

    @FXML
    void onPasteBookPressed(ActionEvent event) {

    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(2), e-> {
            Book copiedBook = Book.readFromString(Clipboard.getSystemClipboard().getString());
            pasteButton.setDisable(copiedBook == null);
            System.out.println("eee");

        }));


    }
}
