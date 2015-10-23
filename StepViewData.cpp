#include "StepViewData.h"
#include "QString"

StepViewData::StepViewData(QObject *parent) : QObject(parent)
{
    m_listblock.append("All");  //defult block choose All Block
    m_SearchState = false;  //search state is false
    m_stateFilter = -1;     //no state filter
    m_NGnumber = 0;         // NG
}
StepViewData::~StepViewData()
{
    m_listblock.clear();
    m_listStepInf.clear();
    m_subListFindResult.clear();
    m_subListStepInf.clear();
}

void StepViewData::searchClicked(QString stepName)
{
    if(!m_SearchState)
    {
        SearchStep(stepName);
        m_SearchState = true;
    }
    else
    {
        //emit toDlg(m_subListStepInf);
        FilterStep(m_stateFilter);
        m_SearchState = false;
    }
}
void StepViewData::stateFilterChange(int state)
{
    switch (state) {

    case 1:
        m_stateFilter = 0;  //NG filter
        FilterStep(0);
        break;
    case 2:
        m_stateFilter = 1;  //OK filter
        FilterStep(1);
        break;
    default:

        m_stateFilter = -1; //no state filter
        emit toDlg(m_subListStepInf);
        break;
    }
}

void StepViewData::blockFilterChange(QString blockName)
{
    m_subListStepInf = m_listStepInf;
    FilterStep(blockName);
    FilterStep(m_stateFilter);
}

bool StepViewData::isNewBlock(QString blockName)
{
    if(0 == m_listblock.length())
        return true;
    else
    {
        for(int i=0; i<m_listblock.length(); i++)
        {
            if(blockName == m_listblock.at(i))
                return false;
        }
    }
    return true;
}

void StepViewData::addBlock(QString &blockName)
{

    //int l = m_listblock.length();
    bool insertLast = true;

    for(int i=0; i<m_listblock.length() && insertLast; i++)
    {

        if(blockName < m_listblock.at(i))
        {
            m_listblock.insert(i++, blockName);
            insertLast = false;
        }

    }
    if(insertLast)
        m_listblock.append(blockName);

    emit toDlgBlockChange(m_listblock);

}

void StepViewData::clearBlock()
{
    //m_listblock.begin() = "All";
    for(int i=1; i<m_listblock.length(); i++)
    {
        m_listblock.removeAt(i--);
        if(i < 0) break;
    }
    emit toDlgBlockChange(m_listblock);
}

void StepViewData::AppendVariable(StepInf stepinf)
{

    if(isNewBlock(stepinf.blockName))
        addBlock(stepinf.blockName);  //add new block name

    //need to emit a signal!

    m_listStepInf.append(stepinf);

    m_subListStepInf.append(stepinf);

    if(0 == stepinf.stepState) m_NGnumber++;

    emit toDlg(m_subListStepInf);// sub!!!

}

void StepViewData::AppendVariable(QString stepName, QString blockName, int stepState, QString imformation)
{

    if(isNewBlock(blockName))
        addBlock(blockName);  //add new block name

    //need to emit a signal!

    m_varStepInf.stepName = stepName;

    m_varStepInf.blockName = blockName;

    m_varStepInf.stepState = stepState;

    m_varStepInf.imformation = imformation;

    m_listStepInf.append(m_varStepInf);

    m_subListStepInf.append(m_varStepInf);

    if(0 == stepState) m_NGnumber++;

    emit toDlg(m_subListStepInf);// sub!!!

}

void  StepViewData::setSubListAll()
{

    m_subListStepInf = m_listStepInf;

    emit toDlg(m_subListStepInf);// sub!!!
}

bool StepViewData::FilterStep(QString blockName)
{

    if(blockName.length() == 0 )
        return true;
    if(blockName == "All")
    {
        setSubListAll();
        return true;
    }


    for(int i=0; i<m_subListStepInf.length() && i>=0; i++)
    {

        if(m_subListStepInf[i].blockName != blockName)
        {

            m_subListStepInf.removeAt(i);

            i--;

        }


    }

    emit toDlg(m_subListStepInf);// sub!!!

    return true;   
}

ListStepInf StepViewData::FilterStep(int stepState )
{

    if(stepState == -1)
    {
        emit toDlg(m_subListStepInf);
        return m_subListStepInf;
    }
    ListStepInf tmp = m_subListStepInf;
    for(int i=0; i<tmp.length() && i>=0; i++)
    {

        if(tmp[i].stepState != stepState)
        {

            tmp.removeAt(i);

            i--;

        }

    }

    emit toDlg(tmp);// sub!!!
    return tmp;
}

bool StepViewData::SearchStep(QString stepName)
{

    if(stepName.length() == 0)
        return false;

    m_subListFindResult.clear();

    ListStepInf tmplist = FilterStep(m_stateFilter);
    for(int i=0; i<tmplist.length(); i++)
    {

        if(tmplist[i].stepName == stepName)
        {

            m_subListFindResult.append(tmplist[i]);

        }

    }

    emit toDlg(m_subListFindResult);// sub!!!

    return true;
}

StepInf StepViewData::at(int index, bool isSubList)
{

    if(isSubList)
        return m_listStepInf.at(index);

    return m_subListStepInf.at(index);

}


void StepViewData::removeAt(int index, bool notSubList)
{

    if(notSubList)
        return m_listStepInf.removeAt(index);

    return m_subListStepInf.removeAt(index);

}


void StepViewData::Clear()
{

    m_listStepInf.clear();
    m_subListStepInf.clear();
    m_NGnumber = 0;

    emit toDlg(m_subListStepInf);// sub!!!

    clearBlock();
    //need to emit a signal!
}


void StepViewData::deleteStep(QString StepName, QString blockName)
{
    if(StepName == "")
        return ;
    if(blockName == "")
    {

        for(int i=0; i<m_listStepInf.length() && i>=0; i++)
        {

            if(m_listStepInf.at(i).stepName == StepName )
            {
                if(m_listStepInf.at(i).stepState == 0) {m_NGnumber--;}
                m_listStepInf.removeAt(i--);
            }

        }

        for(int i=0; i<m_subListStepInf.length() && i>=0; i++)
        {

            if(m_subListStepInf.at(i).stepName == StepName )
            {
                m_subListStepInf.removeAt(i--);
            }

        }

    }
    else
    {

        for(int i=0; i<m_listStepInf.length() && i>=0; i++)
        {

            if(m_listStepInf.at(i).blockName == blockName )
            {

                if(m_listStepInf.at(i).stepName == StepName )
                {
                    m_listStepInf.removeAt(i--);
                }

            }

        }
        for(int i=0; i<m_subListStepInf.length() && i>=0; i++)
        {

            if(m_subListStepInf.at(i).blockName == blockName )
            {

                if(m_subListStepInf.at(i).stepName == StepName )
                {
                    m_subListStepInf.removeAt(i--);
                }

            }

        }

    }

    emit toDlg(m_subListStepInf);// sub!!!

}

void StepViewData::deleteBlock(QString blockName)
{
    if(blockName == "")
        return ;

    for(int i=0; i<m_listStepInf.length() && i>=0; i++)
    {

        if(m_listStepInf.at(i).blockName == blockName )
        {
            if(m_listStepInf.at(i).stepState == 0) {m_NGnumber--;}
            m_listStepInf.removeAt(i--);
        }

    }
    for(int i=0; i<m_subListStepInf.length() && i>=0; i++)
    {

        if(m_subListStepInf.at(i).blockName == blockName )
        {
            m_subListStepInf.removeAt(i--);
        }

    }

    emit toDlg(m_subListStepInf);// sub!!!

    for(int i=0; i<m_listblock.length() && i>=0; i++)
    {

        if(blockName == m_listblock.at(i))
        {
            m_listblock.removeAt(i);
            break;
        }

    }

    emit toDlgBlockChange(m_listblock);

}

int StepViewData::length()
{
    return m_listStepInf.length();
}

int StepViewData::subLlength()
{
    return m_subListStepInf.length();
}

int StepViewData::blockCount()
{
    return (m_listblock.length()-1);
}

int StepViewData::stepCount()
{
    return m_listStepInf.length();
}

int StepViewData::NGstepCount()
{
    return m_NGnumber;
}

bool StepViewData::runState()
{
    if(m_NGnumber == 0)
        return true;
    return false;
}


