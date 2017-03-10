//
// Created by matteo on 03/03/17.
//
#include "ResourceFile.h"
#include <list>


#ifndef PROGRESSBAR_FILESQUEUE_H
#define PROGRESSBAR_FILESQUEUE_H

#include "Subject.h"
#include "Observer.h"

class Observer;

class FilesQueue : public Subject {
public:
    FilesQueue() : size(0), pushed(false), removed(false) { }

    ~FilesQueue() { }

    int getSize() const {
        return size;
    }

    void setSize(int s) {
        size = s;
    }

    virtual void subscribe(Observer *o) {
        attachedObs.push_front(o);
    }

    virtual void unsubscribe(Observer *o) {
        attachedObs.remove(o);
    }

    virtual void notify();

    void addFileToQueue(ResourceFile &file);

    void removeFileFromQueue();


    bool testFilesQueue(FilesQueue *fq);


private:
    std::list<ResourceFile> queue;
    std::list<Observer *> attachedObs;
    int size;
    bool removed;
    bool pushed;

};

#endif //PROGRESSBAR_FILESQUEUE_H
