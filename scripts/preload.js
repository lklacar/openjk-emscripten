function downloadAsset(pakName) {
    return fetch('http://localhost:8000/base/' + pakName)
        .then(resp => resp.blob())
        .then(blob => blob.arrayBuffer())
        .then(data => {
            const x = new Uint8Array(data);
            // noinspection JSUnresolvedFunction,JSUnresolvedVariable
            FS.writeFile('/base/' + pakName, x);
            console.log("Done: " + pakName)
        })
        .catch(console.log);
}

// noinspection JSUnresolvedFunction,JSUnresolvedVariable
Module.noInitialRun = true;

// noinspection JSUnresolvedFunction,JSUnresolvedVariable
Module.preInit = function () {
    setTimeout(() => {
        // noinspection JSUnresolvedFunction,JSUnresolvedVariable
        FS.mkdir('/base');

        Promise.all([
            downloadAsset("assets0.pk3"),
            downloadAsset("assets1.pk3"),
            downloadAsset("assets2.pk3"),
            downloadAsset("assets3.pk3"),
            downloadAsset("default.cfg"),
        ]).then(() => {

            window.shouldRunNow = true;
            window.calledRun = false;

            // noinspection JSUnresolvedFunction,JSUnresolvedVariable
            Module.run();
        })
    }, 500)
}