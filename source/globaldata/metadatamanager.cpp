#include "metadatamanager.h"

#include <QDebug>
#include <QDataStream>

MetaDataManager::MetaDataManager()
{
    loadDefaultSymbolTable();
}

MetaDataManager::~MetaDataManager()
{

}

void MetaDataManager::setCellCode (quint64 id, QString code)
{
    _idCellMetaDataMap[id].computerCode = code;
}

QString MetaDataManager::getCellCode (quint64 id)
{
    if( _idCellMetaDataMap.contains(id) )
        return _idCellMetaDataMap[id].computerCode;
    else
        return "";
}

/*void MetaDataManager::setCellColorNumber (quint64 id, quint8 color)
{
    _idCellMetaDataMap[id].colorNumber = color;
}

quint8 MetaDataManager::getCellColorNumber (quint64 id)
{
    if( _idCellMetaDataMap.contains(id) )
        return _idCellMetaDataMap[id].colorNumber;
    else
        return 0;
}
*/

void MetaDataManager::setCellName (quint64 id, QString name)
{
    _idCellMetaDataMap[id].name = name;
}

QString MetaDataManager::getCellName (quint64 id)
{
    if( _idCellMetaDataMap.contains(id) )
        return _idCellMetaDataMap[id].name;
    else
        return "";
}

void MetaDataManager::setCellDescription (quint64 id, QString descr)
{
    _idCellMetaDataMap[id].description = descr;
}

QString MetaDataManager::getCellDescription (quint64 id)
{
    if( _idCellMetaDataMap.contains(id) )
        return _idCellMetaDataMap[id].description;
    else
        return "";
}

void MetaDataManager::setClusterName (quint64 id, QString name)
{
    _idCellMetaDataMap[id].clusterName = name;
}

QString MetaDataManager::getClusterName (quint64 id)
{
    if( _idCellMetaDataMap.contains(id) )
        return _idCellMetaDataMap[id].clusterName;
    else
        return "";
}

void MetaDataManager::setAndUniteClusterName (const QList< quint64 >& ids, QString clusterName)
{
    foreach(quint64 id, ids) {
        setClusterName(id, clusterName);
    }
}

QString MetaDataManager::getAndUniteClusterName (const QList< quint64 >& ids)
{
    //count the names
    QMap< QString, int > namesCount;
    foreach(quint64 id, ids) {
        if( _idCellMetaDataMap.contains(id) ) {
            QString clusterName = _idCellMetaDataMap[id].clusterName;
            namesCount[clusterName] = namesCount[clusterName]+1;
        }
        else {
            namesCount[QString()] = namesCount[QString()]+1;
        }

    }

    //determine the most counted name
    QString mostCountedName;
    int mostCount = 0;
    QMapIterator< QString, int > it(namesCount);
    while( it.hasNext() ) {
        it.next();
        QString clusterName = it.key();
        int count = it.value();
        if( count > mostCount ) {
            mostCount = count;
            mostCountedName = clusterName;
        }
    }

    //set cluster name to all cells in the cluster
    setAndUniteClusterName(ids, mostCountedName);

    return mostCountedName;
}

void MetaDataManager::cleanUp (const QSet< quint64 >& ids)
{
    QMutableMapIterator< quint64, AlienCellMetaData > it(_idCellMetaDataMap);
    while(it.hasNext()) {
        it.next();
        quint64 id = it.key();
        if( !ids.contains(id) ) {
            it.remove();
        }
    }
}

const QMap< quint64, AlienCellMetaData >& MetaDataManager::getCellMetaData ()
{
    return _idCellMetaDataMap;
}

void MetaDataManager::loadDefaultSymbolTable ()
{
    clearSymbolTable();

    //general variables
    addSymbolEntry("i","[255]");
    addSymbolEntry("j","[254]");
    addSymbolEntry("k","[253]");
    addSymbolEntry("l","[252]");

    //token branch number
    addSymbolEntry("BRANCH_NUMBER","[0]");

    //energy guidance system
    addSymbolEntry("ENERGY_GUIDANCE_IN","[1]");
    addSymbolEntry("ENERGY_GUIDANCE_IN::DEACTIVATED","0");
    addSymbolEntry("ENERGY_GUIDANCE_IN::BALANCE_CELL","1");
    addSymbolEntry("ENERGY_GUIDANCE_IN::BALANCE_TOKEN","2");
    addSymbolEntry("ENERGY_GUIDANCE_IN::BALANCE_BOTH","3");
    addSymbolEntry("ENERGY_GUIDANCE_IN::HARVEST_CELL","4");
    addSymbolEntry("ENERGY_GUIDANCE_IN::HARVEST_TOKEN","5");
    addSymbolEntry("ENERGY_GUIDANCE_IN_VALUE_CELL","[2]");
    addSymbolEntry("ENERGY_GUIDANCE_IN_VALUE_TOKEN","[3]");

    //constructor
    addSymbolEntry("CONSTR_OUT","[5]");
    addSymbolEntry("CONSTR_OUT::SUCCESS","0");
    addSymbolEntry("CONSTR_OUT::SUCCESS_ROT","1");
    addSymbolEntry("CONSTR_OUT::ERROR_NO_ENERGY","2");
    addSymbolEntry("CONSTR_OUT::ERROR_OBSTACLE","3");
    addSymbolEntry("CONSTR_OUT::ERROR_CONNECTION","4");
    addSymbolEntry("CONSTR_OUT::ERROR_DIST","5");
    addSymbolEntry("CONSTR_IN","[6]");
    addSymbolEntry("CONSTR_IN::DO_NOTHING","0");
    addSymbolEntry("CONSTR_IN::SAFE","1");
    addSymbolEntry("CONSTR_IN::UNSAFE","2");
    addSymbolEntry("CONSTR_IN::BRUTEFORCE","3");
    addSymbolEntry("CONSTR_IN_OPTION","[7]");
    addSymbolEntry("CONSTR_IN_OPTION::STANDARD","0");
    addSymbolEntry("CONSTR_IN_OPTION::CREATE_EMPTY_TOKEN","1");
    addSymbolEntry("CONSTR_IN_OPTION::CREATE_DUP_TOKEN","2");
    addSymbolEntry("CONSTR_IN_OPTION::FINISH_NO_SEP","3");
    addSymbolEntry("CONSTR_IN_OPTION::FINISH_WITH_SEP","4");
    addSymbolEntry("CONSTR_IN_OPTION::FINISH_WITH_SEP_RED","5");
    addSymbolEntry("CONSTR_IN_OPTION::FINISH_WITH_TOKEN_SEP_RED","6");
    addSymbolEntry("CONSTR_INOUT_ANGLE","[15]");
    addSymbolEntry("CONSTR_IN_DIST","[16]");
    addSymbolEntry("CONSTR_IN_CELL_MAX_CONNECTIONS","[17]");
    addSymbolEntry("CONSTR_IN_CELL_MAX_CONNECTIONS::AUTO","0");
    addSymbolEntry("CONSTR_IN_CELL_BRANCH_NO","[18]");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION","[19]");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::COMPUTER","0");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::PROP","1");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::SCANNER","2");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::WEAPON","3");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::CONSTR","4");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION::SENSOR","5");
    addSymbolEntry("CONSTR_IN_CELL_FUNCTION_DATA","[30]");

    //propulsion
    addSymbolEntry("PROP_OUT","[5]");
    addSymbolEntry("PROP_OUT::SUCCESS","0");
    addSymbolEntry("PROP_OUT::SUCCESS_FINISHED","1");
    addSymbolEntry("PROP_OUT::ERROR_NO_ENERGY","2");
    addSymbolEntry("PROP_IN","[8]");
    addSymbolEntry("PROP_IN::DO_NOTHING","0");
    addSymbolEntry("PROP_IN::BY_ANGLE","1");
    addSymbolEntry("PROP_IN::FROM_CENTER","2");
    addSymbolEntry("PROP_IN::TOWARD_CENTER","3");
    addSymbolEntry("PROP_IN::ROTATION_CLOCKWISE","4");
    addSymbolEntry("PROP_IN::ROTATION_COUNTERCLOCKWISE","5");
    addSymbolEntry("PROP_IN::DAMP_ROTATION","6");
    addSymbolEntry("PROP_IN_ANGLE","[9]");
    addSymbolEntry("PROP_IN_POWER","[10]");

    //scanner
    addSymbolEntry("SCANNER_OUT","[5]");
    addSymbolEntry("SCANNER_OUT::SUCCESS","0");
    addSymbolEntry("SCANNER_OUT::FINISHED","1");
    addSymbolEntry("SCANNER_OUT::RESTART","2");
//    addSymbolEntry("SCANNER_IN","[11]");
    addSymbolEntry("SCANNER_INOUT_CELL_NUMBER","[12]");
    addSymbolEntry("SCANNER_OUT_MASS","[13]");
    addSymbolEntry("SCANNER_OUT_ENERGY","[14]");
    addSymbolEntry("SCANNER_OUT_ANGLE","[15]");
    addSymbolEntry("SCANNER_OUT_DIST","[16]");
    addSymbolEntry("SCANNER_OUT_CELL_MAX_CONNECTIONS","[17]");
    addSymbolEntry("SCANNER_OUT_CELL_BRANCH_NO","[18]");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION","[19]");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::COMPUTER","0");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::PROP","1");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::SCANNER","2");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::WEAPON","3");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::CONSTR","4");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION::SENSOR","5");
    addSymbolEntry("SCANNER_OUT_CELL_FUNCTION_DATA","[30]");

    //weapon
    addSymbolEntry("WEAPON_OUT","[5]");
    addSymbolEntry("WEAPON_OUT::NO_TARGET","0");
    addSymbolEntry("WEAPON_OUT::STRIKE_SUCCESSFUL","1");

    //sensor
    addSymbolEntry("SENSOR_OUT", "[5]");
    addSymbolEntry("SENSOR_OUT::NOTHING_FOUND", "0");
    addSymbolEntry("SENSOR_OUT::CLUSTER_FOUND", "1");
    addSymbolEntry("SENSOR_IN", "[20]");
    addSymbolEntry("SENSOR_IN::DO_NOTHING", "0");
    addSymbolEntry("SENSOR_IN::SEARCH_VICINITY", "1");
    addSymbolEntry("SENSOR_IN::SEARCH_BY_ANGLE", "2");
    addSymbolEntry("SENSOR_IN::SEARCH_FROM_CENTER", "3");
    addSymbolEntry("SENSOR_IN::SEARCH_TOWARD_CENTER", "4");
    addSymbolEntry("SENSOR_INOUT_ANGLE", "[21]");
    addSymbolEntry("SENSOR_IN_MIN_MASS", "[22]");
    addSymbolEntry("SENSOR_IN_MAX_MASS", "[23]");
    addSymbolEntry("SENSOR_OUT_MASS", "[24]");
    addSymbolEntry("SENSOR_OUT_DIST", "[25]");
}

void MetaDataManager::addSymbolEntry (QString key, QString value)
{
    _symbolTable[key] = value;
}

void MetaDataManager::delSymbolEntry (QString key)
{
    _symbolTable.remove(key);
}

QString MetaDataManager::applySymbolTableToCode (QString input)
{
    if( _symbolTable.contains(input) ) {
        return _symbolTable[input];
    }
    return input;
}

void MetaDataManager::clearSymbolTable ()
{
    _symbolTable.clear();
}

const QMap< QString, QString >& MetaDataManager::getSymbolTable ()
{
    return _symbolTable;
}

void MetaDataManager::setSymbolTable (const QMap< QString, QString >& table)
{
    _symbolTable = table;
}

void MetaDataManager::serializeMetaDataCell (QDataStream& stream, quint64 clusterId, quint64 cellId)
{
    //cell data
    quint32 size = 1;
    stream << size;
    QString code = getCellCode(cellId);
//        quint8 color = getCellColorNumber(cellId);
    QString name = getCellName(cellId);
    QString descr = getCellDescription(cellId);
    QString clusterName = getClusterName(cellId);
    stream << cellId << code << name << descr << clusterName;
}

void MetaDataManager::serializeMetaDataEnsemble (QDataStream& stream, const QList< quint64 >& clusterIds, const QList< quint64 >& cellIds)
{
    //cell data
    quint32 size = cellIds.size();
    stream << size;
    foreach(quint64 cellId, cellIds) {
        QString code = getCellCode(cellId);
//        quint8 color = getCellColorNumber(cellId);
        QString name = getCellName(cellId);
        QString descr = getCellDescription(cellId);
        QString clusterName = getClusterName(cellId);
        stream << cellId << code << name << descr << clusterName;
    }

    //cluster data
/*    size = clusterIds.size();
    stream << size;
    foreach(quint64 clusterId, clusterIds) {
        stream << clusterId << getClusterName(clusterId);
    }*/
}

void MetaDataManager::readMetaData (QDataStream& stream, const QMap< quint64, quint64 >& oldNewClusterIdMap, const QMap< quint64, quint64 >& oldNewCellIdMap)
{
    //cell data
    quint32 size = 0;
    stream >> size;
    quint64 id = 0;
    QString code;
//    quint8 color = 0;
    QString name;
    QString descr;
    QString clusterName;
    for(quint32 i = 0; i < size; ++i) {
        stream >> id >> code >> name >> descr >> clusterName;
        if( oldNewCellIdMap.contains(id) ) {
            setCellCode(oldNewCellIdMap[id], code);
//            setCellColorNumber(oldNewCellIdMap[id], color);
            setCellName(oldNewCellIdMap[id], name);
            setCellDescription(oldNewCellIdMap[id], descr);
            setClusterName(oldNewCellIdMap[id], clusterName);
        }
    }

    //cluster data
/*    stream >> size;
    for(int i = 0; i < size; ++i) {
        stream >> id >> name;
        if( oldNewClusterIdMap.contains(id) ) {
            setClusterName(oldNewClusterIdMap[id], name);
        }
    }*/
}

void MetaDataManager::serializeMetaDataUniverse (QDataStream& stream)
{
    //cell data
    quint32 size = _idCellMetaDataMap.size();
    stream << size;
    QMapIterator< quint64, AlienCellMetaData > it(_idCellMetaDataMap);
    while(it.hasNext()) {
        it.next();
        quint64 cellId = it.key();
        AlienCellMetaData cellMeta = it.value();
        stream << cellId << cellMeta.computerCode << cellMeta.name << cellMeta.description << cellMeta.clusterName;
    }

    //cluster data
/*    size = _idClusterMetaDataMap.size();
    stream << size;
    QMapIterator< quint64, AlienCellClusterMetaData > it2(_idClusterMetaDataMap);
    while(it2.hasNext()) {
        it2.next();
        quint64 clusterId = it2.key();
        AlienCellClusterMetaData clusterMeta = it2.value();
        stream << clusterId << clusterMeta.clusterName;
    }*/
}

void MetaDataManager::readMetaDataUniverse (QDataStream& stream, const QMap< quint64, quint64 >& oldNewClusterIdMap, const QMap< quint64, quint64 >& oldNewCellIdMap)
{
    _idCellMetaDataMap.clear();
    readMetaData(stream, oldNewClusterIdMap, oldNewCellIdMap);
}

void MetaDataManager::serializeSymbolTable (QDataStream& stream)
{
    stream << _symbolTable;
}

void MetaDataManager::readSymbolTable (QDataStream& stream, bool merge)
{
    if( !merge )
        _symbolTable.clear();
    QMap< QString, QString > newSymbolTable;
    stream >> newSymbolTable;
    QMapIterator< QString, QString > it(newSymbolTable);
    while(it.hasNext()) {
        it.next();
        _symbolTable.insert(it.key(), it.value());
    }
}





