//
// Created by matteo on 23/02/17.
//

#include "ProgressBar.h"


void ProgressBar::update(FilesQueue *fq) {
    fq->removeFileFromQueue();
    m_gauge1->SetValue((m_gauge1->GetValue() + 1));
    wxYield();
    updated = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void FilesQueue::notify() {
    for (auto &itr : attachedObs) {
        itr->update(this);
    }
}

void FilesQueue::addFileToQueue(ResourceFile &file) {
    queue.push_front(file);
    size += file.getSize();
    pushed = true;
    if (!attachedObs.empty()) {
        notify();
    }

}

void FilesQueue::removeFileFromQueue() {
    auto p = queue.begin();
    size -= p->getSize();
    queue.pop_front();
    removed = true;

}


bool FilesQueue::testFilesQueue(FilesQueue *fq) {
    bool are_working = false;
    setSize(10);
    if (getSize() == 10)
        std::cout << "setSize and getSize working!" << std::endl;
    else
        std::cout << "setSize or getSize not working!" << std::endl;
    ResourceFile test_unit;
    addFileToQueue(test_unit);
    if (pushed && removed)
        std::cout << "addFile, removeFile and notify working!" << std::endl;
    else
        std::cout << "addFile, removeFile or notify not working!" << std::endl;

    if ((getSize() == 10) && pushed && removed)
        are_working = true;
    return are_working;
}

bool ProgressBar::testProgressBar(ProgressBar *pb) {
    bool is_working = false;
    FilesQueue test_queue;
    ResourceFile test_file;
    test_queue.addFileToQueue(test_file);
    if (pb->updated) {
        is_working = true;
        std::cout << "Update method working!" << std::endl;
    }
    else
        std::cout << "Update method not working!" << std::endl;
    return is_working;
}
