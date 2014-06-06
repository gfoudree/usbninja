#include "virusscan.h"

VirusScan::VirusScan(TrayNotify *tn)
{
    numSignatures = 0;
    fTypes[0] = ".EXE";
    fTypes[1] = ".BAT";
    fTypes[2] = ".BIN";
    fTypes[3] = ".DLL";
    fTypes[4] = ".COM";
    fTypes[5] = ".INF";
    fTypes[6] = ".INI";
    fTypes[7] = ".PDF";
    fTypes[8] = ".DOC";
    fTypes[9] = ".DOCX";
    fTypes[10] = ".PPT";
    fTypes[11] = ".PPTX";
    fTypes[12] = ".SYS";
    fTypes[13] = ".VBS";

    /* Init AV engine */
    int res = cl_init(0);
    cl = cl_engine_new();
    if (res != CL_SUCCESS)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to initialize AV engine: ", (char*)cl_strerror(res));
        std::cout << cl_strerror(res);
        return;
    }

    res = cl_load(cl_retdbdir(), cl, &numSignatures, CL_DB_STDOPT);
    if (res != CL_SUCCESS)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to load AV engine signatures. Check for db folder?: ", (char*)cl_strerror(res));
        std::cout << cl_strerror(res);
        return;
    }

    res = cl_engine_compile(cl);
    if (res != CL_SUCCESS)
    {
        ErrorLog::logErrorToFile("*CRITICAL*", "Unable to compile AV engine rules: ", (char*)cl_strerror(res));
        std::cout << cl_strerror(res);
        return;
    }

    char msgStr[100];
    sprintf(msgStr, "ClamAV engine initialized. %d signatures loaded.", numSignatures);

    ErrorLog::logErrorToFile("*INFO*", msgStr);
    tn->sendMessage(msgStr, "ClamAV");
    tn->setHoverMessage("UsbNinja Daemon\nClamAV Loaded");

}

VirusScan::~VirusScan()
{
    cl_engine_free(cl);
}

std::string VirusScan::getFileExtention(std::string fileName)
{
    size_t pos = fileName.find_last_of('.');
    if (pos == std::string::npos)
        return "";
    else
        return fileName.substr(pos);
}

std::vector<std::string> VirusScan::findFiles(char devName)
{
    std::vector<std::string> files;

    std::string dirPath;
    dirPath += devName;
    dirPath += ":\\";
    for (boost::filesystem::recursive_directory_iterator end, dir(dirPath); dir != end; dir++)
    {
        std::string fileExt = getFileExtention(dir->path().filename().string());
        boost::to_upper(fileExt);
        for (int i = 0; i < fTypesSz; i++)
        {
            if (fileExt.compare(fTypes[i]) == 0)
            {
                files.push_back(dir->path().string());
                break;
            }
        }
    }
    return files;
}

void VirusScan::lockFiles(std::vector<std::string> files)
{
    std::vector<HANDLE> hFiles; //File handles vector so we can unlock them...

    for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++)
    {
        /* Lock file (null for shared rights) */
        HANDLE hFile = CreateFileA(it->c_str(), GENERIC_READ | GENERIC_WRITE,
                                  0, NULL, OPEN_EXISTING, 0, NULL);
        hFiles.push_back(hFile);
    }
}

char* VirusScan::getVirusName()
{
    return virusName;
}

cl_cvd VirusScan::getCVDInfo(char *file)
{
    cl_cvd ret;
    struct cl_cvd *cc;
    cc = cl_cvdhead(file);

    ret.builder = cc->builder;
    ret.dsig = cc->dsig;
    ret.fl = cc->fl;
    ret.md5 = cc->md5;
    ret.sigs = cc->sigs;
    ret.stime = cc->stime;
    ret.time = cc->time;
    ret.version = cc->version;

    cl_cvdfree(cc);
    return ret;
}
