
#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "purchasedialog.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ClientWindow) {
    ui->setupUi(this);
    connect(ui->btnHome, &QPushButton::clicked, this, &ClientWindow::navigateToHome);
    connect(ui->btnLoja, &QPushButton::clicked, this, &ClientWindow::navigateToEstoque);

    // Conectar ao banco de dados
    if (QSqlDatabase::contains("loja_connection")) {
        db = QSqlDatabase::database("loja_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", "loja_connection");
        db.setDatabaseName("estoque.db");

        if (!db.open()) {
            QMessageBox::critical(this, "Erro", "Falha ao abrir o banco de dados: " + db.lastError().text());
            return;
        }
    }

    // Exibir mensagem de sucesso se o banco de dados for aberto com sucesso
    QMessageBox::information(this, "Sucesso", "Banco de dados conectado com sucesso!");

    // Consultar as estampas e tamanhos no banco de dados
    QSqlQuery query;
    if (!query.exec("SELECT id, estampa, tamanho, SUM(quantidade) AS total FROM entradas GROUP BY id, estampa, tamanho")) {
        qDebug() << "Erro ao executar a consulta:" << query.lastError().text();
        return;
    }

    // Estrutura para armazenar dados agrupados
    QMap<QString, QMap<QString, QPair<int, int>>> estoque; // <estampa, <tamanho, <id, quantidade>>>

    while (query.next()) {
        QString estampa = query.value("estampa").toString();
        QString tamanho = query.value("tamanho").toString();
        int id = query.value("id").toInt();
        int quantidade = query.value("total").toInt();

        estoque[estampa][tamanho] = qMakePair(id, quantidade);
    }


    // Layout para adicionar dinamicamente os frames na página da loja
    QVBoxLayout *layout = new QVBoxLayout();

    for (auto it = estoque.begin(); it != estoque.end(); ++it) {
        QString estampa = it.key();
        QMap<QString, QPair<int, int>> tamanhos = it.value(); // Atualizado para refletir a nova estrutura
        int Quantity;

        // Criar um frame para a estampa
        QFrame *frame = new QFrame(ui->pageLoja);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFixedHeight(180);

        // Layout interno do frame
        QHBoxLayout *frameLayout = new QHBoxLayout(frame);

        // Imagem
        QLabel *imagem = new QLabel(frame);
        QString caminhoImagem = QString(":/images/images/%1.jpg").arg(estampa);
        QPixmap pixmap(caminhoImagem);
        if (pixmap.isNull()) {
            caminhoImagem = QString(":/images/images/%1.jpg").arg(estampa);
            pixmap.load(caminhoImagem);
        }

        if (pixmap.isNull()) {
            qDebug() << "Falha ao carregar a imagem:" << estampa;
        }
        imagem->setPixmap(pixmap.scaled(130, 130, Qt::KeepAspectRatio));
        imagem->setFixedSize(130, 130);
        frameLayout->addWidget(imagem);

        // Detalhes do produto
        QVBoxLayout *detailsLayout = new QVBoxLayout();

        // Nome
        QLabel *lblNome = new QLabel("Estampa: " + estampa, frame);
        detailsLayout->addWidget(lblNome);

        // Preço
        QLabel *lblPreco = new QLabel("Preço: R$ 49,99", frame);
        detailsLayout->addWidget(lblPreco);

        // Estoque por tamanho
        QLabel *lblEstoque = new QLabel("Estoque:", frame);
        detailsLayout->addWidget(lblEstoque);

        QComboBox *cmbTamanhos = new QComboBox(frame);
        for (auto sizeIt = tamanhos.begin(); sizeIt != tamanhos.end(); ++sizeIt) {
            QString tamanho = sizeIt.key();
            int id = sizeIt.value().first;        // Extrair o ID
            int quantidade = sizeIt.value().second; // Extrair a quantidade
            Quantity = quantidade;

            cmbTamanhos->addItem(tamanho + " - " + QString::number(quantidade) + " unidades", id);
        }
        detailsLayout->addWidget(cmbTamanhos);

        // Botões
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QPushButton *btnComprar = new QPushButton("Comprar", frame);
        buttonLayout->addWidget(btnComprar);
        detailsLayout->addLayout(buttonLayout);
        frameLayout->addLayout(detailsLayout);

        connect(btnComprar, &QPushButton::clicked, this, [this, estampa, cmbTamanhos, Quantity]() {
            PurchaseDialog dialog(this);
            dialog.setEstampa(estampa);
            QString tamanhoSelecionado = cmbTamanhos->currentText().split(" - ").first();
            dialog.setTamanho(tamanhoSelecionado);

            int idSelecionado = cmbTamanhos->currentData().toInt(); // Recuperar o ID
            dialog.setId(idSelecionado); // Passar o ID para o diálogo
            dialog.exec();
        });

        // Adicionar o frame ao layout principal
        layout->addWidget(frame);
    }


    // Atualizar o layout da página da loja
    QWidget *lojaWidget = new QWidget();
    lojaWidget->setLayout(layout);
    ui->scrollArea->setWidget(lojaWidget);

    // Configurar o botão para alterar páginas no QStackedWidget
    connect(ui->btnHome, &QPushButton::clicked, this, &ClientWindow::navigateToHome);
    connect(ui->btnLoja, &QPushButton::clicked, this, &ClientWindow::navigateToEstoque);
}

ClientWindow::~ClientWindow() {
    delete ui;
}

void ClientWindow::navigateToHome() {
    ui->stackedWidget->setCurrentIndex(0); // Página inicial
}

void ClientWindow::navigateToEstoque() {
    ui->stackedWidget->setCurrentIndex(1); // Página da loja
}

