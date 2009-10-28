mlc_set_name(vcsn::xml::myDOMErrorHandler);
mlc_set_name(vcsn::xml::xerces_parser);
template <class TropicalKind> struct mlc_name < vcsn::algebra::TropicalSemiring<TropicalKind> > { static std::string of() { return std::string("vcsn::algebra::TropicalSemiring") + "< " + mlc_name<TropicalKind>::of() + " >"; } };
mlc_set_name(vcsn::algebra::TropicalMin);
mlc_set_name(vcsn::algebra::TropicalMax);
template <class Series> struct mlc_name < vcsn::Transducer<Series> > { static std::string of() { return std::string("vcsn::Transducer") + "< " + mlc_name<Series>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::input_projection_helper<S, T> > { static std::string of() { return std::string("vcsn::input_projection_helper") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::output_projection_helper<S, T> > { static std::string of() { return std::string("vcsn::output_projection_helper") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::identity_transducer_helper<S, T> > { static std::string of() { return std::string("vcsn::identity_transducer_helper") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::xml::xml_chooser_base<S, T> > { static std::string of() { return std::string("vcsn::xml::xml_chooser_base") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::xml::xml_chooser<S, T> > { static std::string of() { return std::string("vcsn::xml::xml_chooser") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class T1, class T2> struct mlc_name < vcsn::xml::reference_pair<T1, T2> > { static std::string of() { return std::string("vcsn::xml::reference_pair") + "< " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::Node<T> > { static std::string of() { return std::string("vcsn::xml::Node") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::automatonNode<T> > { static std::string of() { return std::string("vcsn::xml::automatonNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::transducerNode<T> > { static std::string of() { return std::string("vcsn::xml::transducerNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::typeNode<T> > { static std::string of() { return std::string("vcsn::xml::typeNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::contentNode<T> > { static std::string of() { return std::string("vcsn::xml::contentNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::statesNode<T> > { static std::string of() { return std::string("vcsn::xml::statesNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::transitionsNode<T> > { static std::string of() { return std::string("vcsn::xml::transitionsNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::stateNode<T> > { static std::string of() { return std::string("vcsn::xml::stateNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::transitionNode<T> > { static std::string of() { return std::string("vcsn::xml::transitionNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::initialNode<T> > { static std::string of() { return std::string("vcsn::xml::initialNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::finalNode<T> > { static std::string of() { return std::string("vcsn::xml::finalNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::semiringNode<T> > { static std::string of() { return std::string("vcsn::xml::semiringNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::monoidNode<T> > { static std::string of() { return std::string("vcsn::xml::monoidNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::freemonoidNode<T> > { static std::string of() { return std::string("vcsn::xml::freemonoidNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::generatorNode<T> > { static std::string of() { return std::string("vcsn::xml::generatorNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::geometryNode<T> > { static std::string of() { return std::string("vcsn::xml::geometryNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::xml::drawingNode<T> > { static std::string of() { return std::string("vcsn::xml::drawingNode") + "< " + mlc_name<T>::of() + " >"; } };
template <class Auto> struct mlc_name < vcsn::xml::xml_converter<Auto> > { static std::string of() { return std::string("vcsn::xml::xml_converter") + "< " + mlc_name<Auto>::of() + " >"; } };
mlc_set_name(vcsn::xml::XML);
template <typename L> struct mlc_name < vcsn::algebra::AlphabetSet<L> > { static std::string of() { return std::string("vcsn::algebra::AlphabetSet") + "< " + mlc_name<L>::of() + " >"; } };
template <typename A> struct mlc_name < vcsn::algebra::FreeMonoid<A> > { static std::string of() { return std::string("vcsn::algebra::FreeMonoid") + "< " + mlc_name<A>::of() + " >"; } };
template <class CharT> struct mlc_name < utility::generic_int_type<CharT> > { static std::string of() { return std::string("utility::generic_int_type") + "< " + mlc_name<CharT>::of() + " >"; } };
template <typename CharT> struct mlc_name < utility::char_traits<CharT> > { static std::string of() { return std::string("utility::char_traits") + "< " + mlc_name<CharT>::of() + " >"; } };
mlc_set_name(vcsn::algebra::NumericalSemiring);
template <class S, class T> struct mlc_name < vcsn::algebra::DefaultTransposeFun<S, T> > { static std::string of() { return std::string("vcsn::algebra::DefaultTransposeFun") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
mlc_set_name(vcsn::rat::setpm);
mlc_set_name(vcsn::rat::setzero);
mlc_set_name(vcsn::rat::setid);
template <class Series> struct mlc_name < vcsn::Automata<Series> > { static std::string of() { return std::string("vcsn::Automata") + "< " + mlc_name<Series>::of() + " >"; } };
template <typename Self> struct mlc_name < vcsn::TransducerBase<Self> > { static std::string of() { return std::string("vcsn::TransducerBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <typename T> struct mlc_name < vcsn::transducer_traits<T> > { static std::string of() { return std::string("vcsn::transducer_traits") + "< " + mlc_name<T>::of() + " >"; } };
template <typename T> struct mlc_name < vcsn::extension_traits<T> > { static std::string of() { return std::string("vcsn::extension_traits") + "< " + mlc_name<T>::of() + " >"; } };
template <class S, class T> struct mlc_name < vcsn::projection_traits<S, T> > { static std::string of() { return std::string("vcsn::projection_traits") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::output_projection_traits<T> > { static std::string of() { return std::string("vcsn::output_projection_traits") + "< " + mlc_name<T>::of() + " >"; } };
mlc_set_name(vcsn::labels_are_letters);
mlc_set_name(vcsn::labels_are_words);
mlc_set_name(vcsn::labels_are_series);
mlc_set_name(vcsn::labels_are_couples);
template <class Kind, class WordValue, class WeightValue, class SeriesValue, class Letter> struct mlc_name < vcsn::LabelOf<Kind, WordValue, WeightValue, SeriesValue, Letter> > { static std::string of() { return std::string("vcsn::LabelOf") + "< " + mlc_name<Kind>::of() + ", " + mlc_name<WordValue>::of() + ", " + mlc_name<WeightValue>::of() + ", " + mlc_name<SeriesValue>::of() + ", " + mlc_name<Letter>::of() + " >"; } };
mlc_set_name(vcsn::NoTag);
mlc_set_name(vcsn::geometry);
template <typename EdgeLabel> struct mlc_name < vcsn::edge_value<EdgeLabel> > { static std::string of() { return std::string("vcsn::edge_value") + "< " + mlc_name<EdgeLabel>::of() + " >"; } };
mlc_set_name(vcsn::state_value);
template <class Auto_> struct mlc_name < vcsn::generalized_traits<Auto_> > { static std::string of() { return std::string("vcsn::generalized_traits") + "< " + mlc_name<Auto_>::of() + " >"; } };
template <typename Auto, typename EdgeConverter, typename Format> struct mlc_name < vcsn::io::automaton_saver_<Auto, EdgeConverter, Format> > { static std::string of() { return std::string("vcsn::io::automaton_saver_") + "< " + mlc_name<Auto>::of() + ", " + mlc_name<EdgeConverter>::of() + ", " + mlc_name<Format>::of() + " >"; } };
mlc_set_name(vcsn::io::string_out);
template <typename Auto, typename EdgeConverter, typename Format> struct mlc_name < vcsn::io::automaton_loader_<Auto, EdgeConverter, Format> > { static std::string of() { return std::string("vcsn::io::automaton_loader_") + "< " + mlc_name<Auto>::of() + ", " + mlc_name<EdgeConverter>::of() + ", " + mlc_name<Format>::of() + " >"; } };
mlc_set_name(vcsn::io::dot);
mlc_set_name(vcsn::io::transducer_dot);
template <typename Self, typename Etiq> struct mlc_name < vcsn::algorithm_patterns::Comparator<Self, Etiq> > { static std::string of() { return std::string("vcsn::algorithm_patterns::Comparator") + "< " + mlc_name<Self>::of() + ", " + mlc_name<Etiq>::of() + " >"; } };
template <bool B0, typename T> struct mlc_name < vcsn::reference_type<B0, T> > { static std::string of() { return std::string("vcsn::reference_type") + "< " + ((B0)? "true" : "false") + ", " + mlc_name<T>::of() + " >"; } };
template <bool B0, typename T> struct mlc_name < vcsn::iterator_type<B0, T> > { static std::string of() { return std::string("vcsn::iterator_type") + "< " + ((B0)? "true" : "false") + ", " + mlc_name<T>::of() + " >"; } };
template <typename S> struct mlc_name < vcsn::dynamic_traits<S> > { static std::string of() { return std::string("vcsn::dynamic_traits") + "< " + mlc_name<S>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::SyntacticDecorator<S, T> > { static std::string of() { return std::string("vcsn::SyntacticDecorator") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::MetaElement<S, T> > { static std::string of() { return std::string("vcsn::MetaElement") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::Element<S, T> > { static std::string of() { return std::string("vcsn::Element") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
mlc_set_name(vcsn::default_slot_tag);
template <typename S, typename Tag> struct mlc_name < vcsn::SetSlot<S, Tag> > { static std::string of() { return std::string("vcsn::SetSlot") + "< " + mlc_name<S>::of() + ", " + mlc_name<Tag>::of() + " >"; } };
template <typename Self> struct mlc_name < vcsn::Structure<Self> > { static std::string of() { return std::string("vcsn::Structure") + "< " + mlc_name<Self>::of() + " >"; } };
template <typename Self> struct mlc_name < vcsn::virtual_types<Self> > { static std::string of() { return std::string("vcsn::virtual_types") + "< " + mlc_name<Self>::of() + " >"; } };
mlc_set_name(vcsn::undefined_type);
template <class T> struct mlc_name < utility::unique::UniqueListBase<T> > { static std::string of() { return std::string("utility::unique::UniqueListBase") + "< " + mlc_name<T>::of() + " >"; } };
template <typename T> struct mlc_name < utility::unique::uniquelist<T> > { static std::string of() { return std::string("utility::unique::uniquelist") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < utility::unique::UniqueMap<T> > { static std::string of() { return std::string("utility::unique::UniqueMap") + "< " + mlc_name<T>::of() + " >"; } };
mlc_set_name(utility::unique::unifiable);
template <typename T> struct mlc_name < utility::contract::fail<T> > { static std::string of() { return std::string("utility::contract::fail") + "< " + mlc_name<T>::of() + " >"; } };
template <typename S1, typename S2, typename T1, typename T2> struct mlc_name < vcsn::op_add_traits<S1, S2, T1, T2> > { static std::string of() { return std::string("vcsn::op_add_traits") + "< " + mlc_name<S1>::of() + ", " + mlc_name<S2>::of() + ", " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <typename S1, typename S2, typename T1, typename T2> struct mlc_name < vcsn::op_sub_traits<S1, S2, T1, T2> > { static std::string of() { return std::string("vcsn::op_sub_traits") + "< " + mlc_name<S1>::of() + ", " + mlc_name<S2>::of() + ", " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <typename S1, typename S2, typename T1, typename T2> struct mlc_name < vcsn::op_mul_traits<S1, S2, T1, T2> > { static std::string of() { return std::string("vcsn::op_mul_traits") + "< " + mlc_name<S1>::of() + ", " + mlc_name<S2>::of() + ", " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <typename S1, typename S2, typename T1, typename T2> struct mlc_name < vcsn::op_div_traits<S1, S2, T1, T2> > { static std::string of() { return std::string("vcsn::op_div_traits") + "< " + mlc_name<S1>::of() + ", " + mlc_name<S2>::of() + ", " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <typename S1, typename S2, typename T1, typename T2> struct mlc_name < vcsn::op_mod_traits<S1, S2, T1, T2> > { static std::string of() { return std::string("vcsn::op_mod_traits") + "< " + mlc_name<S1>::of() + ", " + mlc_name<S2>::of() + ", " + mlc_name<T1>::of() + ", " + mlc_name<T2>::of() + " >"; } };
template <typename S, bool B0> struct mlc_name < vcsn::SetSlotAttribute<S, B0> > { static std::string of() { return std::string("vcsn::SetSlotAttribute") + "< " + mlc_name<S>::of() + ", " + ((B0)? "true" : "false") + " >"; } };
mlc_set_name(vcsn::algebra::mul_kind);
mlc_set_name(vcsn::algebra::add_kind);
template <class Self> struct mlc_name < vcsn::algebra::SemigroupBase<Self> > { static std::string of() { return std::string("vcsn::algebra::SemigroupBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <class Self> struct mlc_name < vcsn::algebra::MonoidBase<Self> > { static std::string of() { return std::string("vcsn::algebra::MonoidBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::algebra::identity_as<T> > { static std::string of() { return std::string("vcsn::algebra::identity_as") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::algebra::zero_as<T> > { static std::string of() { return std::string("vcsn::algebra::zero_as") + "< " + mlc_name<T>::of() + " >"; } };
template <class Self> struct mlc_name < vcsn::algebra::SemiringBase<Self> > { static std::string of() { return std::string("vcsn::algebra::SemiringBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::op_star_traits<S, T> > { static std::string of() { return std::string("vcsn::op_star_traits") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::op_begin_traits<S, T> > { static std::string of() { return std::string("vcsn::op_begin_traits") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::op_rbegin_traits<S, T> > { static std::string of() { return std::string("vcsn::op_rbegin_traits") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <char B0, char B1> struct mlc_name < vcsn::algebra::static_char_interval<B0, B1> > { static std::string of() { return std::string("vcsn::algebra::static_char_interval") + "< " + "'" + std::string(B0) + "'" + ", " + "'" + std::string(B1) + "'" + " >"; } };
template <typename T> struct mlc_name < utility::limits<T> > { static std::string of() { return std::string("utility::limits") + "< " + mlc_name<T>::of() + " >"; } };
template <class S> struct mlc_name < vcsn::algebra::AlphabetSetBase<S> > { static std::string of() { return std::string("vcsn::algebra::AlphabetSetBase") + "< " + mlc_name<S>::of() + " >"; } };
template <typename S, typename T> struct mlc_name < vcsn::algebra::alphabet_traits<S, T> > { static std::string of() { return std::string("vcsn::algebra::alphabet_traits") + "< " + mlc_name<S>::of() + ", " + mlc_name<T>::of() + " >"; } };
template <class Self> struct mlc_name < utility::iomanip<Self> > { static std::string of() { return std::string("utility::iomanip") + "< " + mlc_name<Self>::of() + " >"; } };
template <class T> struct mlc_name < utility::escaper<T> > { static std::string of() { return std::string("utility::escaper") + "< " + mlc_name<T>::of() + " >"; } };
mlc_set_name(utility::setesc);
template <class Self> struct mlc_name < vcsn::algebra::FreeMonoidBase<Self> > { static std::string of() { return std::string("vcsn::algebra::FreeMonoidBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <class Self> struct mlc_name < vcsn::algebra::SeriesBase<Self> > { static std::string of() { return std::string("vcsn::algebra::SeriesBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <typename T> struct mlc_name < vcsn::algebra::series_traits<T> > { static std::string of() { return std::string("vcsn::algebra::series_traits") + "< " + mlc_name<T>::of() + " >"; } };
template <typename T, typename W, typename M> struct mlc_name < vcsn::algebra::mute_series_impl<T, W, M> > { static std::string of() { return std::string("vcsn::algebra::mute_series_impl") + "< " + mlc_name<T>::of() + ", " + mlc_name<W>::of() + ", " + mlc_name<M>::of() + " >"; } };
template <typename T, typename W, typename M> struct mlc_name < vcsn::algebra::mute_series_traits<T, W, M> > { static std::string of() { return std::string("vcsn::algebra::mute_series_traits") + "< " + mlc_name<T>::of() + ", " + mlc_name<W>::of() + ", " + mlc_name<M>::of() + " >"; } };
mlc_set_name(vcsn::algebra::semiring_slot_tag);
mlc_set_name(vcsn::algebra::monoid_slot_tag);
template <typename Semiring, typename Monoid> struct mlc_name < vcsn::algebra::Series<Semiring, Monoid> > { static std::string of() { return std::string("vcsn::algebra::Series") + "< " + mlc_name<Semiring>::of() + ", " + mlc_name<Monoid>::of() + " >"; } };
template <class T, bool B0> struct mlc_name < utility::DeferrerDebugPart<T, B0> > { static std::string of() { return std::string("utility::DeferrerDebugPart") + "< " + mlc_name<T>::of() + ", " + ((B0)? "true" : "false") + " >"; } };
template <class T, bool B0> struct mlc_name < utility::Deferrer<T, B0> > { static std::string of() { return std::string("utility::Deferrer") + "< " + mlc_name<T>::of() + ", " + ((B0)? "true" : "false") + " >"; } };
template <class T> struct mlc_name < vcsn::algebra::DispatchFunction<T> > { static std::string of() { return std::string("vcsn::algebra::DispatchFunction") + "< " + mlc_name<T>::of() + " >"; } };
template <class T, class U> struct mlc_name < vcsn::algebra::BinaryOp<T, U> > { static std::string of() { return std::string("vcsn::algebra::BinaryOp") + "< " + mlc_name<T>::of() + ", " + mlc_name<U>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::algebra::UnaryOp<T> > { static std::string of() { return std::string("vcsn::algebra::UnaryOp") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::algebra::Value<T> > { static std::string of() { return std::string("vcsn::algebra::Value") + "< " + mlc_name<T>::of() + " >"; } };
template <class Self, class T, class U, class F> struct mlc_name < vcsn::algebra::GenericMatcher<Self, T, U, F> > { static std::string of() { return std::string("vcsn::algebra::GenericMatcher") + "< " + mlc_name<Self>::of() + ", " + mlc_name<T>::of() + ", " + mlc_name<U>::of() + ", " + mlc_name<F>::of() + " >"; } };
template <class Self, class T, class U, class F> struct mlc_name < vcsn::algebra::KRatExpMatcher<Self, T, U, F> > { static std::string of() { return std::string("vcsn::algebra::KRatExpMatcher") + "< " + mlc_name<Self>::of() + ", " + mlc_name<T>::of() + ", " + mlc_name<U>::of() + ", " + mlc_name<F>::of() + " >"; } };
template <class Self, class Series, class T, class Dispatch> struct mlc_name < vcsn::algebra::KRatExpIdentity<Self, Series, T, Dispatch> > { static std::string of() { return std::string("vcsn::algebra::KRatExpIdentity") + "< " + mlc_name<Self>::of() + ", " + mlc_name<Series>::of() + ", " + mlc_name<T>::of() + ", " + mlc_name<Dispatch>::of() + " >"; } };
mlc_set_name(vcsn::state_h);
mlc_set_name(vcsn::edge_h);
mlc_set_name(vcsn::delta_kind::edges);
mlc_set_name(vcsn::delta_kind::states);
template <typename Self> struct mlc_name < vcsn::AutomataBase<Self> > { static std::string of() { return std::string("vcsn::AutomataBase") + "< " + mlc_name<Self>::of() + " >"; } };
template <typename T> struct mlc_name < vcsn::automaton_traits<T> > { static std::string of() { return std::string("vcsn::automaton_traits") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::TransposeView<T> > { static std::string of() { return std::string("vcsn::TransposeView") + "< " + mlc_name<T>::of() + " >"; } };
template <class T> struct mlc_name < vcsn::transpose_traits<T> > { static std::string of() { return std::string("vcsn::transpose_traits") + "< " + mlc_name<T>::of() + " >"; } };