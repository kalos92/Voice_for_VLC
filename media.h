//
// Created by kalos on 26/04/19.
//

#ifndef GOOGLE_ASSISTANT_FOR_VLC_MEDIA_H
#define GOOGLE_ASSISTANT_FOR_VLC_MEDIA_H


#include <string>
#include <vector>

class Media {

public:

    Media()= default;

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const std::string &getPath() const;

    void setPath(const std::string &path);

    const std::string &getFormat() const;

    void setFormat(const std::string &format);

    const std::vector<std::pair<int, int>> &getEpisodeXSeason() const;

    void putEpisodeXSeason(int s, int e);

    Media (const Media &other)
    {
        path = other.path;
        format = other.format;
        title = other.title;
        episode_x_season = other.episode_x_season;
        episodes = other.episodes;
    }

    Media (const Media *other)
    {
        if (this != other) {
            path = other->path;
            format = other->format;
            title = other->title;
            episode_x_season = other->episode_x_season;
            episodes = other->episodes;
        }
    }

    Media &operator=(std::vector<Media>::iterator other) {

            path = other->path;
            format = other->format;
            title = other->title;
            episode_x_season = other->episode_x_season;
            episodes = other->episodes;
        return *this;
    }

    int getEpisodes() const;

    void setEpisodes(int episodes);

    void setEpisodeXSeason(const std::vector<std::pair<int, int>> &episodeXSeason);

private:

    std::string title;
    std::string path;
    std::string format;
    int episodes;
    std::vector<std::pair<int,int>> episode_x_season;




};


#endif //GOOGLE_ASSISTANT_FOR_VLC_MEDIA_H
