package com.pier.book_register.controller;

import com.pier.book_register.model.Book;
import com.pier.book_register.model.BookManager;
import com.pier.book_register.model.UserHandler;
import com.pier.book_register.view.SceneHandler;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TablePosition;
import javafx.scene.control.TableView;
import javafx.scene.input.*;

import java.util.ArrayList;
import java.util.List;

public class BooksController {

    @FXML
    private TableView<Book> bookTable;
    
    @FXML
    private TableColumn<Book, String> isbnColumn;

    @FXML
    private TableColumn<Book, String> titleColumn;

    @FXML
    private TableColumn<Book, String> authorColumn;

    @FXML
    private TableColumn<Book, String> publisherColumn;

    @FXML
    private TableColumn<Book, String> yearColumn;

    final KeyCombination keyCombinationShiftC = new KeyCodeCombination(
            KeyCode.C, KeyCombination.CONTROL_DOWN);

    @FXML
    void onAddBookPressed(ActionEvent event) {

        SceneHandler.getInstance().openCreateBookStage();
    }

    @FXML
    void onLightSwitchPressed(ActionEvent event) {


    }

    @FXML
    void onLogoutPressed(ActionEvent event) {
        UserHandler.getInstance().logout();
        SceneHandler.getInstance().createLoginScene();
    }

    @FXML
    void tableKeyPressed(KeyEvent event) {

        BookManager userBookManager = UserHandler.getInstance().getLoggedUser().getBookManager();
        if(event.getCode() == KeyCode.DELETE) {
            List<Book> booksToRemove = new ArrayList<>();
            for(TablePosition e : this.bookTable.getSelectionModel().getSelectedCells())
            {
                Book selectedBook = userBookManager.getBooks().get(e.getRow());
                booksToRemove.add(selectedBook);
            }
            booksToRemove.forEach(book -> userBookManager.getBooks().removeIf(b -> b == book));
        }
        else if(keyCombinationShiftC.match(event))
        {
            final ClipboardContent content = new ClipboardContent();

            StringBuilder stringBuilder = new StringBuilder();

            for(TablePosition e : this.bookTable.getSelectionModel().getSelectedCells())
            {
                Book selectedBook = userBookManager.getBooks().get(e.getRow());
                stringBuilder.append(selectedBook.toString());
                stringBuilder.append(":");
            }

            content.putString(stringBuilder.toString());
            Clipboard.getSystemClipboard().setContent(content);
        }

    }

    @FXML
    void initialize()
    {
        System.out.println("TNJILTHILERLJK");
        ObservableList<Book> list = UserHandler.getInstance().getLoggedUser().getBookManager().getBooks();
        bookTable.setItems(list);

        isbnColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().isbn()));
        titleColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().title()));
        authorColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().author()));
        publisherColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().publisher()));
        yearColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().year()));

        bookTable.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);


    }

}
