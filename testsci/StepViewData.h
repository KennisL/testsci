#ifndef STEPVIEWDATA_H
#define STEPVIEWDATA_H

#include <QObject>
#include <QList>
#include <QString>
#include "scistepdata.h"

class StepViewData : public QObject
{
    Q_OBJECT

public:

    explicit StepViewData(QObject *parent = 0);

    ~StepViewData();

signals:

    void toDlg(ListStepInf & listStep);

    void toDlgBlockChange(ListBlock & blocklist);

    //void JumpTo(QString blokcName, QString stepName);

public slots:

    void searchClicked(QString stepName);

    void stateFilterChange(int state);

    void blockFilterChange(QString blockName);

    //void JumpCatch(int row);
public:

    bool isNewBlock(QString blockName);

    void addBlock(QString &blockName);

    void clearBlock();

    void AppendVariable(QString blockName,QString stepName, int state, QString imformation = "");

    void AppendVariable(StepInf stepinf);

    void  setSubListAll();             //showStepList = All stepInfList

    bool FilterStep(QString blockName);//filter with the blockname

    ListStepInf FilterStep(int stepState );   //filter with the step state

    bool SearchStep(QString stepName);  //Search step in showStepList

    StepInf at(int index, bool notSubList = true);

    void removeAt(int index, bool notSubList = true);

    //int findStep(QString stepName, bool notSubList = true);

    void deleteStep(QString StepName, QString blockName = "");

    void deleteBlock(QString blockName);


    void Clear();

    int length();

    int subLlength();

    int blockCount();

    int stepCount();

    int NGstepCount();

    bool runState();


private:

    StepInf m_varStepInf;

    ListStepInf m_subListFindResult;

    QString m_blockFilter;

    int m_stateFilter;                    //1: OK filter

    int m_NGnumber;                     //NG number

    bool m_SearchState;

    ListBlock m_listblock;              // Save block name

    ListStepInf m_listStepInf;          //Save all of the step imformation of SCI project

    ListStepInf m_subListStepInf;       //showStepList, Save the step imformation witch is the UI display
};

#endif // STEPVIEWDATA_H
