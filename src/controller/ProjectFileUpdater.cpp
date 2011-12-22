#include "ProjectFileUpdater.h"
#include "../Utils.h"

ProjectFileUpdater::ProjectFileUpdater()
{
    //ctor
}

void ProjectFileUpdater::updateFile(ProjectFile& projFile, GitFileStatus& gitStatus) {
    updateFile(projFile, gitStatus.getStatus());
}

void ProjectFileUpdater::updateFile(ProjectFile& projFile, GitFileStatus::FileStatus fileStatus) {
    projFile.SetFileState(convert(fileStatus));
}

FileVisualState ProjectFileUpdater::convert(GitFileStatus::FileStatus fileStatus) {
    if (fileStatus == GitFileStatus::added) {
        return fvsVcAdded;
    } else if (fileStatus == GitFileStatus::modified) {
        return fvsVcModified;
    } else if (fileStatus == GitFileStatus::untracked) {
        return fvsVcNonControlled;
    }
    return fvsNormal;

}

ProjectFileUpdater::~ProjectFileUpdater()
{
    //dtor
}
