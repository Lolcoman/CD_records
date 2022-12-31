#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{
//Inicializace prázdných proměných v konstruktoru
public:
    Record(const QString &Author="",
           const QString &Album="",
           const QString &AlbumYear="",
           const QString &MusicGenre="",
           const QString &Playlist="",
           const QByteArray &Booklet=QByteArray());
    QString Author()const{return pAuthor;}
    QString Album()const{return pAlbum;}
    QString AlbumYear()const{return pAlbumYear;}
    QString MusicGenre()const{return pMusicGenre;}
    QString Playlist()const{return pPlaylist;}
    QByteArray Booklet()const{return pBooklet;}
private:
    QString pAuthor;
    QString pAlbum;
    QString pAlbumYear;
    QString pMusicGenre;
    QString pPlaylist;
    QByteArray pBooklet;
};

#endif // RECORD_H
