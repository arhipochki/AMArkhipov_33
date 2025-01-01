#include <sstream>

#include "Chess.h"
#include "ChessType.h"

#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"

Chess::Chess(std::string launch_path)
{
    size_t found = launch_path.find_last_of("/\\");
    this->launch_path = launch_path.substr(0, found);

    std::map<std::string, std::string> textures = {
        {"background",this->launch_path + "\\imgs\\background.jpg"},
        {"field", this->launch_path + "\\imgs\\field.jpg"},
        {"wP", this->launch_path + "\\imgs\\wP.png"},
        {"wH", this->launch_path + "\\imgs\\wH.png"},
        {"wB", this->launch_path + "\\imgs\\wB.png"},
        {"wR", this->launch_path + "\\imgs\\wR.png"},
        {"wK", this->launch_path + "\\imgs\\wK.png"},
        {"wQ", this->launch_path + "\\imgs\\wQ.png"},
        {"bP", this->launch_path + "\\imgs\\bP.png"},
        {"bH", this->launch_path + "\\imgs\\bH.png"},
        {"bB", this->launch_path + "\\imgs\\bB.png"},
        {"bR", this->launch_path + "\\imgs\\bR.png"},
        {"bK", this->launch_path + "\\imgs\\bK.png"},
        {"bQ", this->launch_path + "\\imgs\\bQ.png"}
    };

    int choice = rand() % 2;

    // HERE SHOULD BE A GRAPHICAL INPUT, BUT NOPE
    std::string name;
    std::cout << "Input a name of the first player: ";
    std::cin >> name;
    players[0] = new Player(name, game_time_mseconds);
    std::cout << "\n";

    std::cout << "Input a name of the second player: ";
    std::cin >> name;
    players[1] = new Player(name, game_time_mseconds);
    std::cout << "\n";

    players[1]->setStartTeam(ChessTeam::White); // Белые снизу доски
    players[0]->setStartTeam(ChessTeam::Black);

    // Если повезло, то второй игро будет ходить первым
    if (choice)
    {
        Player* t = players[1];
        players[1] = players[0];
        players[0] = t;

        players[1]->setStartTeam(ChessTeam::White);
        players[0]->setStartTeam(ChessTeam::Black);
    }

    players[1]->changeClock();

    window = SDL_CreateWindow("Chess?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    isRunning = init();

    std::string font_path = this->launch_path + "\\fonts\\DePixelKlein.ttf";
    font = openFont(font_path, 64);

    for (auto pair : textures)
        loaded_textures[pair.first] = loadTexture(renderer, pair.second);

    textures.clear();

    int kings_pos = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            ChessTeam team = (i < N / 2 ? ChessTeam::Black : ChessTeam::White);
            int way = (i < N / 2) ? 1 : -1;
            switch (chess_map[i][j])
            {
            case 'P':
                figures.push_back(new Pawn(renderer, loaded_textures[std::string(1, (char)team) + "P"], j, i, TILE_SIZE, ChessType::Pawn, team, way));
                break;
            case 'R':
                figures.push_back(new Rook(renderer, loaded_textures[std::string(1, (char)team) + "R"], j, i, TILE_SIZE, ChessType::Rook, team));
                break;
            case 'B':
                figures.push_back(new Bishop(renderer, loaded_textures[std::string(1, (char)team) + "B"], j, i, TILE_SIZE, ChessType::Bishop, team));
                break;
            case 'N':
                figures.push_back(new Knight(renderer, loaded_textures[std::string(1, (char)team) + "H"], j, i, TILE_SIZE, ChessType::Knight, team));
                break;
            case 'K':
                kings[kings_pos] = new King(renderer, loaded_textures[std::string(1, (char)team) + "K"], j, i, TILE_SIZE, ChessType::King, team);
                figures.push_back(kings[kings_pos++]);
                break;
            case 'Q':
                figures.push_back(new Queen(renderer, loaded_textures[std::string(1, (char)team) + "Q"], j, i, TILE_SIZE, ChessType::Queen, team));
                break;
            default:
                break;
            }
        }
}

Chess::~Chess()
{
    for (auto pair : loaded_textures)
        SDL_DestroyTexture(pair.second);

    for (auto fig : figures)
        delete fig;

    figures.clear();

    loaded_textures.clear();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    for (int i = 0; i < 2; i++)
    {
        delete players[i];
        SDL_DestroyTexture(font_images[i]);
        SDL_DestroyTexture(font_times[i]);
    }

    SDL_DestroyTexture(last_message);

    TTF_CloseFont(font);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Chess::checkCheckmate()
{
    if (game_started && !game_ended)
    {
        std::map<ChessTeam, bool> zero_moves;

        for (int i = 0; i < 2; i++)
            zero_moves[kings[i]->getTeam()] = false;

        for (int i = 0; i < 2; i++)
        {
            if (kings[i]->isAttacked()) // Если король атакован, то проверяем ходы фигур его команды
            {
                for (auto fig : figures)
                {
                    if (fig->getTeam() == kings[i]->getTeam())
                    {
                        checkPossibleWays(fig);
                        
                        if (fig->getPossibleWays().empty())
                            zero_moves[fig->getTeam()] = true;
                        else // Если есть хоть 1 ход, то ещё не мат
                        {
                            zero_moves[fig->getTeam()] = false;
                            break;
                        }
                    }
                }
            }
        }
        
        if (!game_ended)
        {
            for (auto it : zero_moves)
            {
                if (it.second)
                {
                    winner = "Checkmate for " + std::string(1, (char)it.first);
                    logger.warning(winner);
                    game_ended = true;
                }
            }
        }
    }
}

void Chess::checkTheCheck()
{
    for (int i = 0; i < 2; i++)
    {
        kings[i]->setAttacked(false); // Выставляем, что король не атакован
        for (auto fig : figures)    // Пытаемся его атаковать
            fig->canAttack(chess_map, kings[i]);
    }
}

void Chess::checkPossibleWays(Figure* figure)
{
    figure->checkAllPossibleWays(chess_map); // Получаем все ходы фигуры

    for (auto fig : figures)    // Проверяем, какие фигуры она может атаковать
        figure->canAttack(chess_map, fig);

    Figure* ff = new Figure(figure); // Делаем копию фигуры, чтобы просчитывать её ходы

    int start_x = ff->getMapX(); // Начальный x
    int start_y = ff->getMapY(); // Начальный y

    char copy_map[N][N]; // Копия карты, по который будем считать

    if (figure->getType() == ChessType::King) // Фигура король, то у него будет свой просчёт ходов
    {
        for (auto fig : figures)
        {
            if (fig->getType() != ChessType::Pawn)
                fig->checkAllPossibleWays(chess_map);
            fig->canAttack(chess_map, figure);
        }

        for (auto fig : figures) // Удаляем все ходы, которые под боем
            figure->removeIntersectedWays(fig);

        for (auto way : ff->getPossibleWays())
        {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    copy_map[i][j] = chess_map[i][j];

            auto copy_figures = figures;

            ff->move(copy_map, copy_figures, way.second, way.first);

            ff->setAttacked(false);
            for (auto fig : copy_figures)
                fig->canAttack(copy_map, ff);

            if (ff->isAttacked()) // Если после хода король атакован, то удаляем ход
                figure->eraseMove(way);

            ff->setMapX(start_x);
            ff->setMapY(start_y);
        }
    }
    else
    {
        for (auto way : ff->getPossibleWays())
        {
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    copy_map[i][j] = chess_map[i][j];

            auto copy_figures = figures;

            ff->move(copy_map, copy_figures, way.second, way.first);

            for (int i = 0; i < 2; i++)
            {
                kings[i]->setAttacked(false);
                for (auto fig : copy_figures)
                    fig->canAttack(copy_map, kings[i]);

                // Если после хода король атакован, то удаляем ход
                if (kings[i]->isAttacked() && ff->getTeam() == kings[i]->getTeam())
                    figure->eraseMove(way);
            }

            ff->setMapX(start_x);
            ff->setMapY(start_y);
        }
    }

    delete ff;
}

void Chess::draw()
{
    renderTexture(renderer, loaded_textures["background"], 0, 0, WIDTH, HEIGHT);
    renderTexture(renderer, loaded_textures["field"], FIELD_X - 1.2 * BOARD_ERR, FIELD_Y, FIELD_WIDTH + BOARD_ERR, FIELD_HEIGHT + 1.4 * BOARD_ERR);

    for (auto fig : figures)
        fig->draw();

    for (int i = 0; i < 2; i++)
    {
        if (kings[i]->isAttacked())
            drawRect(renderer, kings[i]->getTextureX() + TILE_SIZE / 4, kings[i]->getTextureY() + TILE_SIZE / 4,
                TILE_SIZE / 2, TILE_SIZE / 2, SDL_Color{ 255, 0, 0 });
    }

    for (int i = 0; i < 2; i++)
    {
        font_images[i] = renderText(renderer, font, players[i]->getName(), SDL_Color{ 255, 255, 255 });
        font_times[i] = renderText(renderer, font, players[i]->getGameTime(), SDL_Color{ 255, 255, 255 });
    }

    renderTexture(renderer, font_images[0], PLAYER_LABEL_X, FIRST_PLAYER_LABEL_Y, 150, 50);
    renderTexture(renderer, font_times[0], PLAYER_LABEL_X, FIRST_PLAYER_LABEL_Y + 50, 150, 50);

    renderTexture(renderer, font_images[1], PLAYER_LABEL_X, SECOND_PLAYER_LABEL_Y, 150, 50);
    renderTexture(renderer, font_times[1], PLAYER_LABEL_X, SECOND_PLAYER_LABEL_Y + 50, 150, 50);

    if (game_ended)
    {
        last_message = renderText(renderer, font, winner, SDL_Color{ 255, 255, 255 });
        renderTexture(renderer, last_message, WIDTH / 4, HEIGHT / 2, 400, 100);
    }
}

void Chess::run()
{
    SDL_Event event;

    Figure* figure_selected = nullptr;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                    game_ended = true;
                }
                if (event.key.keysym.sym == SDLK_p)
                    game_ended = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                Uint32 buttons;

                SDL_PumpEvents();  // Получаем последние события

                buttons = SDL_GetMouseState(&x, &y); // 1 - левая, 4 - правая

                // Если курсор покрывает поле
                if (x > FIELD_X && x < FIELD_X + FIELD_WIDTH &&
                    y > FIELD_Y && y < FIELD_Y + FIELD_HEIGHT)
                {
                    if (figure_selected == nullptr)
                    {
                        // Ищем фигуру по координатам
                        auto found = std::find_if(figures.begin(), figures.end(),
                            [&x, &y](Figure* fig)
                            {
                                return (x > fig->getTextureX() && x < fig->getTextureX() + fig->getSize() &&
                                    y > fig->getTextureY() && y < fig->getTextureY() + TILE_SIZE);
                            }
                        );

                        // Если нашли и команда текущего хода совпадает, то запоминаем
                        if (found != figures.end() && ((Figure*)*found)->getTeam() == current_team_move)
                            figure_selected = *found;
                    }
                    else
                    {
                        int move_to_x = (x - FIELD_X) / TILE_SIZE;
                        int move_to_y = (y - FIELD_Y) / TILE_SIZE;

                        if ((move_to_x != figure_selected->getMapX() ||
                            move_to_y != figure_selected->getMapY()) && !game_ended)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                if (players[i]->getTeam() == current_team_move)
                                {
                                    game_started = true;
                                    bool was_moved = false;

                                    players[i]->moveFigure(figure_selected, move_to_x, move_to_y, &was_moved, chess_map, figures);

                                    if (was_moved)
                                    {
                                        if (current_team_move == ChessTeam::White)
                                            current_team_move = ChessTeam::Black;
                                        else
                                            current_team_move = ChessTeam::White;

                                        for (int i = 0; i < 2; i++)
                                            players[i]->changeClock();
                                    }

                                    break;
                                }
                            }
                        }

                        figure_selected = nullptr;
                    }
                }

                break;
            }
        }

        SDL_RenderClear(renderer);

        takeTime();

        checkTheCheck();

        draw();

        // Если фигура выбрана, то просчитываем её ходы и отрисовываем ходы
        if (figure_selected != nullptr) 
        {
            checkPossibleWays(figure_selected);
            
            figure_selected->drawWays();
        }

        checkCheckmate();

        printStatistics();

        SDL_RenderPresent(renderer);
    }
}

void Chess::printStatistics()
{
    if (game_ended && !statistics_shown)
    {
        std::stringstream ss;

        logger.information("Final statistics:");
        for (int i = 0; i < 2; i++)
        {
            players[i]->stopClock();

            logger.information("Eaten figures by " + players[i]->getName());
            logger.information("Total amount of eaten figures: " + std::to_string(players[i]->getEatenFigures().size()));
            
            for (auto fig : players[i]->getEatenFigures())
                ss << (char)fig->getTeam() << (char)fig->getType() << " ";
            logger.information(ss.str());
            ss.str("");

            logger.information("Figures, that was eaten by an eaten figure: ");
            for (auto fig : players[i]->getEatenFigures())
            {
                ss << (char)fig->getTeam() << (char)fig->getType() << ": ";
                for (auto ff : fig->getEatenFigures())
                    ss << (char)ff->getTeam() << (char)ff->getType() << " ";
                logger.information(ss.str());
                ss.str("");
            }
        }

        logger.information("Figures, that was eaten by a figure (on the board):");
        for (auto fig : figures)
        {
            ss << (char)fig->getTeam() << (char)fig->getType() << " has eaten: ";
            logger.information(ss.str());
            ss.str("");

            for (auto ff : fig->getEatenFigures())
                ss << (char)ff->getTeam() << (char)ff->getType() << " ";
            logger.information(ss.str());
            ss.str("");
        }

        logger.information("History of moves (figures on the board):");
        for (auto fig : figures)
        {
            int count = 1;
            ss << "History of " << (char)fig->getTeam() << (char)fig->getType() 
                << ". Total amount of moves: " << fig->getHistoryOfMoves().size();
            logger.information(ss.str());
            ss.str("");
            for (auto move : fig->getHistoryOfMoves())
            {
                ss << count++ << ". " << FIELD_LETTERS.at(move.second) << move.first;
                logger.information(ss.str());

                ss.str("");
            }
        }

        logger.information("History of moves (eaten figures):");
        for (int i = 0; i < 2; i++)
        {
            for (auto fig : players[i]->getEatenFigures())
            {
                int count = 1;
                ss << "History of " << (char)fig->getTeam() << (char)fig->getType() 
                    << ". Total amount of moves: " << fig->getHistoryOfMoves().size();
                logger.information(ss.str());
                ss.str("");
                for (auto move : fig->getHistoryOfMoves())
                {
                    ss << count++ << ". " << FIELD_LETTERS.at(move.second) << move.first;
                    logger.information(ss.str());
                    ss.str("");
                }
            }
        }

        std::chrono::milliseconds total_time(0);
        for (int i = 0; i < 2; i++)
        {
            logger.information("Elapsed time by " + players[i]->getName());
            int secs = round((game_time_mseconds.count() - players[i]->getRawTime().count()) % (60 * 1000) / 1000);
            int mins = (game_time_mseconds.count() - players[i]->getRawTime().count()) / (60 * 1000);
            logger.information(std::to_string(mins) 
                + ":" + (secs < 10 ? "0" + std::to_string(secs) : std::to_string(secs)).substr(0, 2));

            total_time += game_time_mseconds - players[i]->getRawTime();
        }
        int secs = round(total_time.count() % (60 * 1000) / 1000);
        logger.information("Total elapsed time: " + std::to_string(total_time.count() / (60 * 1000)) + ":" 
            + (secs < 10 ? "0" + std::to_string(secs) : std::to_string(secs)).substr(0, 2));

        statistics_shown = true;
    }
}

void Chess::takeTime()
{
    for (int i = 0; i < 2; i++)
        if (players[i]->getClock())
            players[i]->takeElapsedTime(std::chrono::milliseconds(17));
}
