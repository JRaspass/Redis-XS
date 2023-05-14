requires 'XSLoader' => '0.14';  # For XSLoader::load with no arguments.
requires 'perl'     => 'v5.14';

on build => sub {
    requires 'ExtUtils::ParseXS' => '3.12'; # For embedded typemaps.
};

on test => sub {
    requires 'Test2::Suite' => '0.000072';  # For Test2::V0.
    requires 'Test2::Tools::xUnit';
};
