/*
 * OngoingNotification.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */



void createOngoingNotification(OngoingNotification* this_gen){

}
void setOngoingNotificationTitle(OngoingNotification* this_gen,char* title){

}
void setOngoingNotificationText(OngoingNotification* this_gen,char* text){

}
void setOngoingNotificationIcon(OngoingNotification* this_gen,char* imagePath){

}

void deleteOngoingNotification(OngoingNotification* this_gen){
    if(this_gen != NULL) {
        OngoingNotificationExtends* this = (OngoingNotificationExtends*) this_gen;
        if(NULL!=this->title)
            free(this->title);
        if(NULL!=this->text)
            free(this->text);
        if(NULL!=this->imagePath)
            free(this->imagePath);

        free(this);
        this->OngoingNotification=NULL;


    }
}

OngoingNotification* newOngoingNotification(){
    OngoingNotificationExtends *this;

    this= (OngoingNotificationExtends*) malloc(sizeof(OngoingNotificationExtends));
    this->OngoingNotification.create= createOngoingNotification;
    this->OngoingNotification.delete= deleteOngoingNotification;
    this->OngoingNotification.setTitle=setOngoingNotificationTitle;
    this->OngoingNotification.setText=setOngoingNotificationText;
    this->OngoingNotification.setIcon=setOngoingNotificationIcon;
    this->title=NULL;
    this->text=NULL;
    this->imagePath=NULL;


    return &this->OngoingNotification;
}

