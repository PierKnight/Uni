package com.pier.text_editor.model;

public class EditFile {
    private String fileName;
    private String content;
    private String path;
    private boolean isNewFile;

    public EditFile(String fileName, String content, String path) {
        this.fileName = fileName;
        this.content = content;
        this.path = path;
        this.isNewFile = false;
    }

    public EditFile()
    {
        this("untitled","","");
        this.isNewFile = true;
    }

    public String getFileName() {
        return fileName;
    }

    public String getContent() {
        return content;
    }

    public String getPath() {
        return path;
    }

    public boolean isNewFile() {
        return isNewFile;
    }


    public void completeFile(String title,String content,String path){
        this.isNewFile = false;
        this.fileName = title;
        this.content = content;
        this.path = path;
    }

}
