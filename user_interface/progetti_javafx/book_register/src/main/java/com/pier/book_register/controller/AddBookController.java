package com.pier.book_register.controller;

import com.pier.book_register.model.Book;
import com.pier.book_register.model.UserHandler;
import com.pier.book_register.view.SceneHandler;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.control.Tooltip;
import javafx.stage.Stage;
import javafx.util.Duration;

public class AddBookController {

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
    void initialize()
    {
    }

}
