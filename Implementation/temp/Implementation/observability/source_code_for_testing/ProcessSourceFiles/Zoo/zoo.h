// ============================================================================
// Exemplo expandido para TCC - Sistema de Zoológico
// Explora herança pública, protegida e privada.
// ============================================================================

// Classe base genérica
class Animal {};

// -------------------------
// Grupos principais
// -------------------------
class Mamifero : public Animal {};
class Ave : protected Animal {};
class Reptil : private Animal {};
class Peixe : public Animal {};
class Anfibio : protected Animal {};

// -------------------------
// Mamíferos concretos
// -------------------------
class Leao : public Mamifero {};
class Tigre : protected Mamifero {};
class Elefante : private Mamifero {};
class Gato : public Mamifero {};
class Cachorro : public Mamifero {};

// -------------------------
// Aves concretas
// -------------------------
class Papagaio : public Ave {};
class Aguia : protected Ave {};
class Pato : private Ave {};
class Corvo : public Ave {};
class Pinguim : protected Ave {};

// -------------------------
// Répteis concretos
// -------------------------
class Cobra : public Reptil {};
class Jacare : protected Reptil {};
class Lagarto : private Reptil {};
class Tartaruga : public Reptil {};
class Iguana : protected Reptil {};

// -------------------------
// Peixes concretos
// -------------------------
class Tubarao : public Peixe {};
class Tilapia : protected Peixe {};
class Salmao : private Peixe {};
class Atum : public Peixe {};
class PeixePalhaco : public Peixe {};

// -------------------------
// Anfíbios concretos
// -------------------------
class Sapo : public Anfibio {};
class Salamandra : protected Anfibio {};
class Ra : private Anfibio {};
class Tritao : public Anfibio {};
class Perereca : protected Anfibio {};

// ============================================================================
// Exemplo de múltipla herança
// ============================================================================
class AnimalAquatico {
public:
    virtual void nadar() = 0;
};

class AnimalVoador {
public:
    virtual void voar() = 0;
};

class PatoAquatico : public Pato, public AnimalAquatico {};
class AguiaReal : public Aguia, public AnimalVoador {};
class PinguimImperador : public Pinguim, public AnimalAquatico {};
class SapoNadador : public Sapo, protected AnimalAquatico {};
class Dragao : public Reptil, protected AnimalVoador, private AnimalAquatico {};

// ============================================================================
// Recursos do zoológico
// ============================================================================
class Recurso {};

class Jaula : public Recurso {};
class Viveiro : protected Recurso {};
class Aquario : private Recurso {};
class Terrario : public Recurso {};
class Lago : protected Recurso {};

// ============================================================================
// Funcionários
// ============================================================================
class Funcionario : public Recurso {};
class Veterinario : public Funcionario {};
class Cuidador : protected Funcionario {};
class Administrador : private Funcionario {};
class Estagiario : public Funcionario {};
class Pesquisador : protected Funcionario {};

// ============================================================================
// Sistemas de gestão
// ============================================================================
class SistemaGerenciamento {};
class SistemaFinanceiro : public SistemaGerenciamento {};
class SistemaVeterinario : protected SistemaGerenciamento {};
class SistemaVisitantes : private SistemaGerenciamento {};
class SistemaIngressos : public SistemaGerenciamento {};
class SistemaLogistica : protected SistemaGerenciamento {};

// ============================================================================
// Heranças cruzadas complexas
// ============================================================================
class Zoologico {};
class ZoologicoUrbano : public Zoologico, public SistemaGerenciamento {};
class ZoologicoRural : protected Zoologico, private SistemaFinanceiro {};
class ZoologicoDigital : public Zoologico, protected SistemaVisitantes {};
class ZoologicoTematico : private Zoologico, public SistemaIngressos {};
class ZoologicoAquatico : public Zoologico, protected AnimalAquatico {};

// ============================================================================
// Classes adicionais para atingir ~200 linhas
// ============================================================================
class Onca : public Mamifero {};
class Morcego : protected Mamifero, public AnimalVoador {};
class Cavalo : private Mamifero {};
class Galinha : public Ave {};
class Arara : protected Ave {};
class JacareDoPantanal : public Jacare {};
class Camaleao : private Lagarto {};
class CobraCascavel : public Cobra {};
class TubaraoBranco : protected Tubarao {};
class TilapiaAfricana : public Tilapia {};
class SalmaoDoPacifico : protected Salmao {};
class PeixeBeta : private PeixePalhaco {};
class SapoCururu : public Sapo {};
class SalamandraTigre : private Salamandra {};
class TritaoGigante : protected Tritao {};
class PererecaVerde : public Perereca {};
class DragaoDeKomodo : public Dragao {};
class DragaoChines : protected Dragao {};
class DragaoNegro : private Dragao {};
class ZoologicoVirtual : public ZoologicoDigital {};
class ZoologicoInfantil : protected ZoologicoTematico {};
class ZoologicoMontanha : private ZoologicoRural {};
