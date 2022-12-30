#include "record.h"

Record::Record(const QString &author,
               const QString &album,
               const QString &albumYear,
               const QString &musicGenre,
               const QString &playlist,
               const QByteArray &booklet)
{
    pAuthor = author;
    pAlbum = album;
    pAlbumYear = albumYear;
    pMusicGenre = musicGenre;
    pPlaylist = playlist;
    pBooklet = booklet;
}
